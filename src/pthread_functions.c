/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthread_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:12:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/21 15:58:51 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

static int	malloc_philos(pthread_t **threads, t_philo **philo_d, t_data *data)
{
	*threads = malloc(data->num_philos * sizeof(pthread_t));
	*philo_d = malloc(data->num_philos * sizeof(t_philo));
	if (*threads == NULL || *philo_d == NULL)
	{
		free(*threads);
		free(*philo_d);
		return (-1);
	}
	return (0);
}

static int	handle_thread_error(pthread_t *threads, t_philo *philo)
{
	free(threads);
	free(philo);
	write(STDERR_FILENO, "Error while creating threads\n", 29);
	return (-1);
}

int	init_philosophers(pthread_t **threads, \
							t_philo **philo_d, t_data *data)
{
	int	i;

	i = 0;
	if (malloc_philos(threads, philo_d, data) == -1)
		return (-1);
	while (i < data->num_philos)
	{
		(*philo_d)[i].id = i + 1;
		(*philo_d)[i].shared = data;
		if (pthread_create(*threads + i, NULL, philo_loop, *philo_d + i) == -1)
			return (handle_thread_error(*threads, *philo_d));
		usleep(10);
		i++;
	}
	return (0);
}

int	run_threads(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philo_d;
	int			i;

	i = 0;
	if (pthread_mutex_init(&data->abort_lock, NULL) \
		|| pthread_mutex_init(&data->mic, NULL))
		return (-1);
	if (init_philosophers(&threads, &philo_d, data) == -1)
		return (-1);
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	free(philo_d);
	return (0);
}

pthread_mutex_t	*init_mutexes(int philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	philos += 1;
	forks = malloc(philos * sizeof(pthread_mutex_t));
	if (forks)
	{
		while (i < philos)
		{
			if (pthread_mutex_init((forks + i), NULL) == -1)
			{
				free(forks);
				return (NULL);
			}
			i++;
		}
	}
	return (forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthread_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:12:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/14 17:08:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

/*
int	set_abort(t_data *data)
{
	pthread_mutex_lock(data->forks + data->philos);
	if (data-abort)
	{

		return (1);
	}
}
*/

static int	malloc_philos(pthread_t **threads, t_philo **philo_data)
{
	*threads = malloc(data->num_philos * sizeof(pthread_t));
	*philos = malloc(data->num_philos * sizeof(t_philo));
	if (*threads == NULL || *philos == NULL)
	{
		free(*threads);
		free(*philos);
		return (-1);
	}
	return (0);
}

static pthread_t	*handle_thread_error(pthread_t *threads, t_philo *philo)
{
	free(threads);
	free(philos);
	write(STDERR_FILENO, "Error while creating threads\n", 29);
	return (NULL);
}

pthread_t	init_philosophers(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philo_d;
	int			i;

	i = 0;
	if (malloc_philos(&threads, &philo_d))
		return (-1);
	while (i < data->philos)
	{
		philo_data[i]->id = i + 1;
		philo_data[i]->shared = data;
		if (pthread_create(threads + i, NULL, philo_loop, philo_d + i) == -1)
			return (handle_thread_error(threads, philo_d);
		usleep(10);
		i++;
	}
	return (threads);
}

int	run_threads(t_data *data)
{
	pthread_t	*threads;

	data
	threads = init_philosophers(data);
	if (!threads)
		return (-1);

	pthread_join(threads[0], NULL);
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

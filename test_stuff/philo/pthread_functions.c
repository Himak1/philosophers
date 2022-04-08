/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthread_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:12:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/08 13:47:43 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "philo.h"

static int	malloc_philosophers(pthread_t **threads, \
								t_philo **philo_d, t_data *data)
{
	*threads = malloc(data->num_philos * sizeof(pthread_t));
	*philo_d = malloc(data->num_philos * sizeof(t_philo));
	if (*threads == NULL || *philo_d == NULL)
	{
		free(*threads);
		free(*philo_d);
		return (-1);
	}
	memset(*philo_d, 0, data->num_philos * sizeof(t_philo));
	return (0);
}

static int	handle_thread_error(pthread_t *threads, t_philo *philo, int i)
{
	high_priority_gate(philo->shared);
	philo->shared->abort = CASUALTIES;
	high_priority_exit(philo->shared);
	while (i > -1)
	{
		pthread_join(threads[i], NULL);
		i--;
	}
	write(STDERR_FILENO, "error while creating threads\n", 29);
	return (-1);
}

static int	init_philosophers(pthread_t *threads, t_time *starttime, \
					t_philo *philo_d, t_data *data)
{
	int				i;
	long			start;

	i = 0;
	gettimeofday(starttime, NULL);
	start = (starttime->tv_sec * 1000) + (starttime->tv_usec / 1000);
	while (i < data->num_philos)
	{
		philo_d[i].id = i + 1;
		if (data->num_eat == -1)
			philo_d[i].times_ate = -2;
		philo_d[i].start = start;
		philo_d[i].shared = data;
		philo_d[i].lastmeal.tv_sec = starttime->tv_sec;
		philo_d[i].lastmeal.tv_usec = starttime->tv_usec;
		if (pthread_create(threads + i, NULL, philo_loop, philo_d + i) == -1)
			return (handle_thread_error(threads, philo_d, i - 1));
		i++;
	}
	return (0);
}

int	run_threads(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philo_d;
	t_time		starttime;
	int			i;

	i = 0;
	if (malloc_philosophers(&threads, &philo_d, data) == -1)
		return (-1);
	if (init_philosophers(threads, &starttime, philo_d, data) == -1)
	{
		free(threads);
		free(philo_d);
		return (-1);
	}
	monitor_philos(philo_d, data);
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	free(philo_d);
	return (0);
}

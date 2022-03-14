/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthread_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:12:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/14 14:10:50 by jhille        ########   odam.nl         */
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

int	run_threads(t_data *data)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(data->philos * sizeof(pthread_t));
	if (!threads)
		return (-1);
	while (i < data->philos)
	{
		if (pthread_create(threads + i, NULL, philo_loop, data) == -1)
		{
			// handle error
			write(STDERR_FILENO, "Error while creating threads\n", 29);
		}
		usleep(10);
		i++;
	}
	pthread_join(threads[0], NULL);
	return (0);
}

pthread_mutex_t	*ini_mutexs(int philos)
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

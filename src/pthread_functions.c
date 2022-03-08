/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthread_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:12:17 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/08 18:12:42 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

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
		if (pthread_create(threads + 1, NULL, philo_loop, data) == -1)
		{
			// handle threads in case of error
		}
		i++;
	}
	return (0);
}

pthread_mutex_t	*ini_mutexs(int philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
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

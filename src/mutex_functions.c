/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 16:05:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/22 16:15:42 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i)
	{
		pthread_mutex_destroy(data->forks + i);
		i++;
	}
	pthread_mutex_destroy(&data->abort_lock);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 16:05:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/25 13:02:51 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i)
	{
		pthread_mutex_destroy(data->forks + i);
		i++;
	}
	pthread_mutex_destroy(&data->abort_m);
}

static void	mutex_init_error_cleanup(t_data *data, int i)
{
	while (i > -1)
	{
		pthread_mutex_destroy(data->forks + i);
		i--;
	}
	free(data->forks);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->lowp_m, NULL) || \
		pthread_mutex_init(&data->highp_m, NULL) || \
		pthread_mutex_init(&data->abort_m, NULL))
		return (-1);
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (data->forks)
	{
		while (i < data->num_philos)
		{
			if (pthread_mutex_init((data->forks + i), NULL) == -1)
			{
				mutex_init_error_cleanup(data, i - 1);
				return (-1);
			}
			i++;
		}
	}
	else
		return (-1);
	return (0);
}

/*
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
*/

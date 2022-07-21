/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 16:05:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/08 14:00:10 by jhille        ########   odam.nl         */
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
		pthread_mutex_destroy(data->meal_mutexes + i);
		i++;
	}
	pthread_mutex_destroy(data->lh_gates + 0);
	pthread_mutex_destroy(data->lh_gates + 1);
	free(data->forks);
	free(data->meal_mutexes);
	free(data->lh_gates);
}

static void	mutex_init_error_cleanup(pthread_mutex_t *mutex_array, int i)
{
	while (i > -1)
	{
		pthread_mutex_destroy(mutex_array + i);
		i--;
	}
	free(mutex_array);
}

static pthread_mutex_t	*init_n_mutexes(int n)
{
	pthread_mutex_t	*mutex_array;
	int				i;

	i = 0;
	mutex_array = malloc(n * sizeof(pthread_mutex_t));
	if (!mutex_array)
		return (NULL);
	while (i < n)
	{
		if (pthread_mutex_init(mutex_array + i, NULL))
		{
			mutex_init_error_cleanup(mutex_array, i - 1);
			return (NULL);
		}
		i++;
	}
	return (mutex_array);
}

int	init_mutexes(t_data *data)
{
	data->lh_gates = init_n_mutexes(2);
	if (!data->lh_gates)
		return (-1);
	data->forks = init_n_mutexes(data->num_philos);
	if (!data->forks)
	{
		mutex_init_error_cleanup(data->lh_gates, data->num_philos);
		return (-1);
	}
	data->meal_mutexes = init_n_mutexes(data->num_philos);
	if (!data->meal_mutexes)
	{
		mutex_init_error_cleanup(data->lh_gates, 2);
		mutex_init_error_cleanup(data->forks, data->num_philos);
		return (-1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_access.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 12:43:53 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/25 12:44:46 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	low_priority_access(t_data *data)
{
	pthread_mutex_lock(&data->lowp_m);
	pthread_mutex_lock(&data->highp_m);
	pthread_mutex_lock(&data->abort_m);
	pthread_mutex_unlock(&data->highp_m);
}

void	low_priority_exit(t_data *data)
{
	pthread_mutex_unlock(&data->abort_m);
	pthread_mutex_unlock(&data->lowp_m);
}

void	high_priority_gate(t_data *data)
{
	pthread_mutex_lock(&data->highp_m);
	pthread_mutex_lock(&data->abort_m);
	pthread_mutex_unlock(&data->highp_m);
}

void	high_priority_exit(t_data *data)
{
	pthread_mutex_unlock(&data->abort_m);
}

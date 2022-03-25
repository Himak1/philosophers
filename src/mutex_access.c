/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_access.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 12:43:53 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/25 13:32:23 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	low_priority_access(t_data *data)
{
	pthread_mutex_lock(data->lhm_gates + 0);
	pthread_mutex_lock(data->lhm_gates + 1);
	pthread_mutex_lock(data->lhm_gates + 2);
	pthread_mutex_unlock(data->lhm_gates + 1);
}

void	low_priority_exit(t_data *data)
{
	pthread_mutex_unlock(data->lhm_gates + 2);
	pthread_mutex_unlock(data->lhm_gates + 0);
}

void	high_priority_gate(t_data *data)
{
	pthread_mutex_lock(data->lhm_gates + 1);
	pthread_mutex_lock(data->lhm_gates + 2);
	pthread_mutex_unlock(data->lhm_gates + 1);
}

void	high_priority_exit(t_data *data)
{
	pthread_mutex_unlock(data->lhm_gates + 2);
}

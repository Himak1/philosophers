/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_gates.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 12:43:53 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/31 15:51:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	low_priority_gate(t_data *data)
{
	pthread_mutex_lock(data->lh_gates + 0);
	pthread_mutex_lock(data->lh_gates + 1);
}

void	low_priority_exit(t_data *data)
{
	pthread_mutex_unlock(data->lh_gates + 1);
	pthread_mutex_unlock(data->lh_gates + 0);
}

void	high_priority_gate(t_data *data)
{
	pthread_mutex_lock(data->lh_gates + 1);
}

void	high_priority_exit(t_data *data)
{
	pthread_mutex_unlock(data->lh_gates + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 15:54:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/24 16:57:56 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// print_log returns abort_status, which can only be 0 r 2

int	print_log(t_philo *philo_d, const char *message)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo_d->shared->abort_lock);
	/*
		// should print_log() check for starved status too?

	if (compare_time(&philo_d->cur_time, &philo_d->lastmeal) \
	> philo_d->shared->die)
	{
		printf("%ld %d died\n", get_thread_age(philo_d), philo_d->id);
		ret = CASUALTIES;
	}
	*/
	if (philo_d->shared->abort != CASUALTIES)
		printf("%ld %d %s\n", get_thread_age(philo_d), philo_d->id, message);
	else
		ret = CASUALTIES;
	pthread_mutex_unlock(&philo_d->shared->abort_lock);
	return (ret);
}

int	print_death(t_philo *philo_d)
{
	pthread_mutex_lock(&philo_d->shared->abort_lock);
	if (philo_d->shared->abort != CASUALTIES)
	{
		printf("%ld %d died\n", get_thread_age(philo_d), philo_d->id);
		philo_d->shared->abort = CASUALTIES;
	}
	pthread_mutex_unlock(&philo_d->shared->abort_lock);
	return (CASUALTIES);
}

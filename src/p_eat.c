/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   p_eat.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 16:08:50 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/13 13:00:19 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	single_fork(t_philo *philo_d)
{
	safesleep(philo_d, philo_d->shared->die);
	return (CASUALTIES);
}

static int	grab_forks(t_philo *philo_d, int right_fork)
{
	pthread_mutex_lock(&philo_d->shared->forks[philo_d->id - 1]);
	print_log(philo_d, "grabbed a fork");
	if (philo_d->shared->num_philos == 1)
		return (single_fork(philo_d));
	pthread_mutex_lock(&philo_d->shared->forks[right_fork]);
	return (0);
}

static void	update_lastmeal(t_philo *philo_d)
{
	pthread_mutex_lock(philo_d->shared->meal_mutexes + (philo_d->id - 1));
	gettimeofday(&philo_d->lastmeal, NULL);
	pthread_mutex_unlock(philo_d->shared->meal_mutexes + (philo_d->id - 1));
}

int	p_eat(t_philo *philo_d, int *times_ate)
{
	int	ret;
	int	right_fork;

	if (philo_d->id == philo_d->shared->num_philos)
		right_fork = 0;
	else
		right_fork = philo_d->id;
	if (grab_forks(philo_d, right_fork) == CASUALTIES)
		ret = CASUALTIES;
	else
	{
		print_log(philo_d, "grabbed a fork");
		ret = print_log(philo_d, "is eating");
	}
	if (philo_d->shared->num_eat != -1)
		*times_ate += 1;
	update_lastmeal(philo_d);
	if (ret == 0)
		ret = safesleep(philo_d, philo_d->shared->eat);
	pthread_mutex_unlock(&philo_d->shared->forks[right_fork]);
	pthread_mutex_unlock(&philo_d->shared->forks[philo_d->id - 1]);
	if (ret != 0)
		return (ret);
	return (SLEEP);
}

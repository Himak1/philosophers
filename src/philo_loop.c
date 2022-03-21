/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/21 13:00:33 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

void	print_log(t_philo *philo_d, long time, const char *message)
{
	pthread_mutex_lock(&philo_d->shared->abort_lock);
	pthread_mutex_lock(&philo_d->shared->mic);
	if (philo_d->shared->abort == 2)
	{
		pthread_mutex_unlock(&philo_d->shared->abort_lock);
		pthread_mutex_unlock(&philo_d->shared->mic);
		return ;
	}
	else if (philo_d->shared->abort == 1)
		philo_d->shared->abort = 2;
	printf("%ld %d %s\n", time, philo_d->id, message);
	pthread_mutex_unlock(&philo_d->shared->mic);
	pthread_mutex_unlock(&philo_d->shared->abort_lock);
}

static int	p_think(t_philo *philo_d)
{
	print_log(philo_d, get_thread_age(philo_d), "is thinking");
	return (1);
}

static int	p_eat(t_philo *philo_d)
{
	int	ret;
	int	right_fork;

	ret = 2;
	if (philo_d->id == philo_d->shared->num_philos)
		right_fork = 0;
	else
		right_fork = philo_d->id + 1;
	pthread_mutex_lock(philo_d->shared->forks + philo_d->id);
	print_log(philo_d, get_thread_age(philo_d), "grabbed a fork");
	pthread_mutex_lock(philo_d->shared->forks + right_fork);
	print_log(philo_d, get_thread_age(philo_d), "grabbed a fork");
	print_log(philo_d, get_thread_age(philo_d), "is eating");
	if (safesleep(philo_d, philo_d->shared->eat) == 1)
		ret = 3;
	pthread_mutex_unlock(philo_d->shared->forks + right_fork);
	pthread_mutex_unlock(philo_d->shared->forks + philo_d->id);
	return (ret);
}

static int	p_sleep(t_philo *philo_d)
{
	print_log(philo_d, get_thread_age(philo_d), "is sleeping");
	if (safesleep(philo_d, philo_d->shared->sleep) == 1)
		return (3);
	return (0);
}

void	*philo_loop(void *philo_data)
{
	t_philo	*philo_d;
	int		state;

	philo_d = (t_philo *)philo_data;
	gettimeofday(&philo_d->start, NULL);
	gettimeofday(&philo_d->lastmeal, NULL);
	state = 0;
	while (1)
	{
		if (state == 0)
			state = p_think(philo_d);
		else if (state == 1)
			state = p_eat(philo_d);
		else if (state == 2)
			state = p_sleep(philo_d);
		if (state == 3)
			break ;
		if (amidead(philo_d) == 1 || isanyonedead(philo_d) == 1)
		{
			print_log(philo_d, get_thread_age(philo_d), "died");
			break ;
		}
	}
	return (NULL);
}

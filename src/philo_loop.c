/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/22 17:06:28 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

int	print_log(t_philo *philo_d, long time, const char *message)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo_d->shared->abort_lock);
	if (philo_d->shared->abort == 2)
	{
		ret = philo_d->shared->abort;
		pthread_mutex_unlock(&philo_d->shared->abort_lock);
		return (ret);
	}
	else if (philo_d->shared->abort == 1)
	{
		printf("yeeeeet %d\n", philo_d->id);
		philo_d->shared->abort = 2;
		ret = philo_d->shared->abort;
	}
	printf("%ld %d %s\n", time, philo_d->id, message);
	pthread_mutex_unlock(&philo_d->shared->abort_lock);
	return (ret);
}

static int	p_think(t_philo *philo_d)
{
	if (print_log(philo_d, get_thread_age(philo_d), "is thinking") == -1)
		return (CASUALTIES);
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
	int	ret;

	ret = print_log(philo_d, get_thread_age(philo_d), "is sleeping");
	ret = safesleep(philo_d, philo_d->shared->sleep);
	if (ret)
		return (ret);
	return (0);
}

void	*philo_loop(void *philo_data)
{
	t_philo	*philo_d;
	int		state;

	philo_d = (t_philo *)philo_data;
	gettimeofday(&philo_d->start, NULL);
	gettimeofday(&philo_d->lastmeal, NULL);
	state = THINK;
	while (1)
	{
		if (state == THINK)
			state = p_think(philo_d);
		else if (state == EAT)
			state = p_eat(philo_d);
		else if (state == SLEEP)
			state = p_sleep(philo_d);
		if (state == CASUALTIES)
			break ;
		else if (state == STARVED \
				|| amidead(philo_d) || isanyonedead(philo_d) == 1)
		{
			print_log(philo_d, get_thread_age(philo_d), "died");
			break ;
		}
	}
	return (NULL);
}

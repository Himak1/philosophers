/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/23 14:49:01 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

// print_log returns abort_status, which can only be 0 r 2

int	print_log(t_philo *philo_d, const char *message)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo_d->shared->abort_lock);
	if (philo_d->shared->abort == CASUALTIES)
	{
		ret = philo_d->shared->abort;
		pthread_mutex_unlock(&philo_d->shared->abort_lock);
		return (ret);
	}
	else if (philo_d->shared->abort == STARVED)
	{
		printf("yeeeeet %d\n", philo_d->shared->abort);
		philo_d->shared->abort = CASUALTIES;
		ret = philo_d->shared->abort;
	}
	printf("%ld %d %s\n", get_thread_age(philo_d), philo_d->id, message);
	pthread_mutex_unlock(&philo_d->shared->abort_lock);
	return (ret);
}

// p_think() also returns abort_status. print_log can

static int	p_think(t_philo *philo_d)
{
	if (amidead(philo_d) == 1)
		return (STARVED);
	if (print_log(philo_d, "is thinking") == 2)
		return (CASUALTIES);
	return (EAT);
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
	print_log(philo_d, "grabbed a fork");
	pthread_mutex_lock(philo_d->shared->forks + right_fork);
	print_log(philo_d, "grabbed a fork");
	print_log(philo_d, "is eating");
	ret = safesleep(philo_d, philo_d->shared->eat);
	pthread_mutex_unlock(philo_d->shared->forks + right_fork);
	pthread_mutex_unlock(philo_d->shared->forks + philo_d->id);
	return (ret);
}

static int	p_sleep(t_philo *philo_d)
{
	int	ret;

	if (print_log(philo_d, "is sleeping"))
		return (2);
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
		if (state == STARVED)
		{
			print_log(philo_d, "died");
			break ;
		}
	}
	return (NULL);
}

/*
		else if (state == STARVED \
				|| amidead(philo_d) || isanyonedead(philo_d) == 1)
		{
			print_log(philo_d, get_thread_age(philo_d), "died");
			break ;
		}
*/
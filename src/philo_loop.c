/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/18 12:56:38 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

void	print_log(pthread_mutex_t *mic, long time, \
					const char *message, int id)
{
	pthread_mutex_lock(mic);
	printf("%ld %d %s\n", time, id, message);
	pthread_mutex_unlock(mic);
}

static int	p_think(t_philo *philo_d)
{
	print_log(&philo_d->shared->mic, get_thread_age(philo_d), \
				"is thinking", philo_d->id);
	return (1);
}

static int	p_eat(t_philo *philo_d)
{
	pthread_mutex_lock(philo_d->shared->forks + philo_d->id);
	print_log(&philo_d->shared->mic, get_thread_age(philo_d), \
				"grabbed a fork", philo_d->id);
	pthread_mutex_lock(philo_d->shared->forks + (philo_d->id + 1));
	print_log(&philo_d->shared->mic, get_thread_age(philo_d), \
				"grabbed a fork", philo_d->id);
	print_log(&philo_d->shared->mic, get_thread_age(philo_d), \
				"is eating", philo_d->id);
	safesleep(philo_d, philo_d->shared->eat);
	pthread_mutex_unlock(philo_d->shared->forks + (philo_d->id + 1));
	pthread_mutex_unlock(philo_d->shared->forks + philo_d->id);
	return (2);
}

static int	p_sleep(t_philo *philo_d)
{
	print_log(&philo_d->shared->mic, get_thread_age(philo_d), \
			"is sleeping", philo_d->id);
	safesleep(philo_d, philo_d->shared->sleep);
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
		if (amidead(philo_d) == 1)
			break ;
	}
	return (NULL);
}

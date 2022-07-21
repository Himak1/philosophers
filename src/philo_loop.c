/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/13 14:19:48 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	p_think(t_philo *philo_d, int *should_wait)
{
	if (print_log(philo_d, "is thinking") == CASUALTIES)
		return (CASUALTIES);
	if (*should_wait == 1 && (philo_d->id - 1) % 2 != 0)
	{
		*should_wait = 0;
		safesleep(philo_d, philo_d->shared->eat);
	}
	return (EAT);
}

static int	p_sleep(t_philo *philo_d)
{
	int	ret;

	print_log(philo_d, "is sleeping");
	ret = safesleep(philo_d, philo_d->shared->sleep);
	return (ret);
}

void	*philo_loop(void *philo_data)
{
	t_philo	*philo_d;
	int		state;
	int		should_wait;

	philo_d = (t_philo *)philo_data;
	should_wait = 1;
	state = THINK;
	while (philo_d->times_ate < philo_d->shared->num_eat)
	{
		if (state == THINK)
			state = p_think(philo_d, &should_wait);
		else if (state == EAT)
			state = p_eat(philo_d, &philo_d->times_ate);
		else if (state == SLEEP)
			state = p_sleep(philo_d);
		else if (state == CASUALTIES)
			break ;
	}
	pthread_mutex_lock(&philo_d->shared->meal_mutexes[philo_d->id - 1]);
	philo_d->amidead = 1;
	pthread_mutex_unlock(&philo_d->shared->meal_mutexes[philo_d->id - 1]);
	return (NULL);
}

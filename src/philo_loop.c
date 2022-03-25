/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/25 18:06:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	p_think(t_philo *philo_d)
{
	if (amidead(philo_d))
		return (STARVED);
	else
		return (EAT);
}

static int	p_eat(t_philo *philo_d)
{
	int	ret;
	int	fork_1;
	int	fork_2;

	ret = 2;
	if (philo_d->id % 2 == 0)
		fork_1 = 
	/*
		choose which fork is grabbed depending on 
	*/
	pthread_mutex_lock(&philo_d->shared->forks[fork_1]);
	print_log(philo_d, "grabbed a fork");
	pthread_mutex_lock(&philo_d->shared->forks[fork_2]);
	print_log(philo_d, "grabbed a fork");
	ret = print_log(philo_d, "is eating");
	if (ret != CASUALTIES)
		ret = safesleep(philo_d, philo_d->shared->eat);
	pthread_mutex_unlock(&philo_d->shared->forks[fork_1]);
	pthread_mutex_unlock(&philo_d->shared->forks[fork_2]);
	return (ret);
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

	philo_d = (t_philo *)philo_data;
	state = THINK;
	while (1)
	{
		if (state == THINK)
			state = p_think(philo_d);
		else if (state == EAT)
			state = p_eat(philo_d);
		else if (state == SLEEP)
			state = p_sleep(philo_d);
		else if (state == STARVED)
			state = print_death(philo_d);
		else if (state == CASUALTIES)
			break ;
	}
	return (NULL);
}

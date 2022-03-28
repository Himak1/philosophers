/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/28 16:45:40 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	p_think(t_philo *philo_d)
{
	print_log(philo_d, "is thinking");
	if (amidead(philo_d))
		return (STARVED);
	else
		return (EAT);
}

static void	choose_forks(t_philo *philo_d, int *fork_1, int *fork_2)
{
	int	id;

	id = philo_d->id - 1;
	if (id % 2 == 0)
	{
		*fork_1 = id;
		if (philo_d->id != philo_d->shared->num_philos)
			*fork_2 = id + 1;
		else
			*fork_2 = 0;
	}
	else
	{
		if (philo_d->id != philo_d->shared->num_philos)
			*fork_1 = id + 1;
		else
			*fork_1 = 0;
		*fork_2 = id;
	}
}

static int	p_eat(t_philo *philo_d)
{
	int	ret;
	int	fork_1;
	int	fork_2;

	choose_forks(philo_d, &fork_1, &fork_2);
	pthread_mutex_lock(&philo_d->shared->forks[fork_1]);
	print_log(philo_d, "grabbed a fork");
	pthread_mutex_lock(&philo_d->shared->forks[fork_2]);
	print_log(philo_d, "grabbed a fork");
	ret = print_log(philo_d, "is eating");
	gettimeofday(&philo_d->lastmeal, NULL);
	if (ret != CASUALTIES)
		ret = safesleep(philo_d, philo_d->shared->eat);
	pthread_mutex_unlock(&philo_d->shared->forks[fork_1]);
	pthread_mutex_unlock(&philo_d->shared->forks[fork_2]);
	if (ret == CASUALTIES)
		return (ret);
	return (SLEEP);
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

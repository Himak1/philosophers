/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/08 15:56:43 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	p_think(t_philo *philo_d)
{
	if (print_log(philo_d, "is thinking") == CASUALTIES)
		return (CASUALTIES);
	else
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
	int		id;

	philo_d = (t_philo *)philo_data;
	id = philo_d->id;
	state = THINK;
	if ((philo_d->id - 1) % 2 != 0
		&& philo_d->id != philo_d->shared->num_philos)
		usleep(50);
	while (philo_d->times_ate < philo_d->shared->num_eat)
	{
		if (state == THINK)
			state = p_think(philo_d);
		else if (state == EAT)
			state = p_eat(philo_d, &philo_d->times_ate);
		else if (state == SLEEP)
			state = p_sleep(philo_d);
		else if (state == CASUALTIES || state == STARVED)
			break ;
	}
	pthread_mutex_lock(&philo_d->shared->meal_mutexes[id - 1]);
	philo_d->id = -2;
	pthread_mutex_unlock(&philo_d->shared->meal_mutexes[id - 1]);
	return (NULL);
}

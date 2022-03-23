/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/23 15:58:12 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	p_think(t_philo *philo_d)
{

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
}

static int	p_sleep(t_philo *philo_d)
{
	
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
		else if (statew)
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
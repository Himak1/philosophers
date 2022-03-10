/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 15:39:55 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/10 18:05:39 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

long	fact1k(long milli)
{
	long	micro;

	micro = milli * 1000;
	return (micro);
}

int	milsleep(int milsec)
{
	int		i;
	long	sleepquota;
	long	temp;

	i = 0;
	sleepquota = fact1k((long)milsec);
	while (1)
	{
		if (sleepquota > 1000000)
		{
			if (usleep(1000000) == -1)
				return (-1);
			sleepquota -= 1000000;
		}
		else
		{
			if (usleep(sleepquota) == -1)
				return (-1);
			break ;
		}
	}
	return (0);
}

long	get_thread_age(t_philo *philo)
{
	long	age;

	age = philo->
}

int			print_timestamp(t_philo *philo)
{

}

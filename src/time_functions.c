/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 15:39:55 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/16 12:13:31 by jhille        ########   odam.nl         */
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
	long	sleepquota;

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
	long	sec;
	long	usec;

	gettimeofday(&philo->cur_time, NULL);
	usec = (philo->cur_time.tv_usec - philo->start.tv_usec) / 1000;
	sec = (philo->cur_time.tv_sec - philo->start.tv_sec) * 1000;
	return (sec + usec);
}

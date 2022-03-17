/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 15:39:55 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/17 16:00:32 by jhille        ########   odam.nl         */
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

/*
void	milsleep(int milsec)
{
	long	sleepquota;

	sleepquota = fact1k((long)milsec);
	while (1)
	{
		if (sleepquota > 1000000)
		{
			usleep(1000000);
			sleepquota -= 1000000;
		}
		else
		{
			usleep(sleepquota);
			break ;
		}
	}
}
*/

long	compare_time(struct timeval *time1, struct timeval *time2)
{
	gettimeofday(&time1, NULL);
	return (((time1->tv_usec - time2->tv_usec) / 1000) + \
			(time1->tv_sec - time2->tv_sec) * 1000);
}	

int	amidead(t_philo *philo_d)
{
	if (compare_time(&philo_d->cur_time, &philo_d->lastmeal) \
	> philo_d->shared->die)
		return (-1);
}

void	safesleep(long sleepquota)
{
	struct timeval	start;
	struct timeval	current;
	long			time_passed;

	gettimeofday(&start, NULL);
	while (1)
	{
		if (sleepquota > 10)
			usleep(10000);
		else
			usleep(sleepquota * 1000);
		gettimeofday(&current, NULL);
		time_passed = ((current.tv_usec - start.tv_usec) / 1000) + \
						((current.tv_sec - start.tv_sec) * 1000);
		if (time_passed >= sleepquota)
			return ;
		sleepquota -= time_passed;
	}
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

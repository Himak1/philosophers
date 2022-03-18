/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 15:39:55 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/18 13:12:43 by jhille        ########   odam.nl         */
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

long	compare_time(struct timeval *time1, struct timeval *time2)
{
	gettimeofday(time1, NULL);
	return (((time1->tv_usec - time2->tv_usec) / 1000) + \
			(time1->tv_sec - time2->tv_sec) * 1000);
}	

int	amidead(t_philo *philo_d)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo_d->shared->abort_lock);
	if (philo_d->shared->abort == 1)
		ret = 1;
	if (ret != 1 && compare_time(&philo_d->cur_time, &philo_d->lastmeal) \
	> philo_d->shared->die)
	{
		philo_d->shared->abort = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&philo_d->shared->abort_lock);
	return (ret);
}

void	safesleep(t_philo *philo_d, long sleepquota)
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
		amidead(philo_d);
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

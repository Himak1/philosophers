/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 15:39:55 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/08 11:04:05 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

long	compare_time(t_time *time1, t_time *time2)
{
	gettimeofday(time1, NULL);
	return (((time1->tv_usec - time2->tv_usec) / 1000) + \
			(time1->tv_sec - time2->tv_sec) * 1000);
}	

int	isanyonedead(t_philo *philo_d)
{
	int	ret;

	low_priority_gate(philo_d->shared);
	ret = philo_d->shared->abort;
	low_priority_exit(philo_d->shared);
	return (ret);
}

int	safesleep(t_philo *philo_d, long sleepquota)
{
	t_time	start;
	t_time	current;
	long	time_passed;

	time_passed = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (sleepquota - time_passed > 5)
			usleep(5000);
		else if (sleepquota - time_passed > 0)
			usleep((sleepquota - time_passed) * 1000);
		time_passed = compare_time(&current, &start);
		if (isanyonedead(philo_d))
			return (CASUALTIES);
		else if (time_passed >= sleepquota)
			return (0);
	}
}

long	get_thread_age(t_philo *philo)
{
	long	current_time;

	gettimeofday(&philo->cur_time, NULL);
	current_time = (philo->cur_time.tv_usec / 1000) \
					+ (philo->cur_time.tv_sec * 1000);
	return (current_time - philo->start);
}

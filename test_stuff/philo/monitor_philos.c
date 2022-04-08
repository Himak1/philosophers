/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_philos.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/04 14:02:37 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/08 13:30:09 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static long	getmlsec(t_time *time)
{
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

static void	print_death(t_philo *philo_d, t_data *data, t_time *current_time)
{
	high_priority_gate(data);
	data->abort = CASUALTIES;
	printf("%ld %d died\n", \
		getmlsec(current_time) - philo_d->start, philo_d->id);
	high_priority_exit(data);
	pthread_mutex_unlock(data->meal_mutexes + (philo_d->id - 1));
	return ;
}

static void	single_philo(t_philo *philo_d, t_time *current_time, int die)
{
	long	time_passed;

	while (1)
	{
		gettimeofday(current_time, NULL);
		time_passed = getmlsec(current_time) - philo_d->start;
		if (time_passed > die)
			break ;
		else if (die - time_passed > 5)
			usleep(5000);
		else
			usleep((die - time_passed) * 1000);
	}
	high_priority_gate(philo_d->shared);
	philo_d->shared->abort = CASUALTIES;
	printf("%ld %d died\n", \
		getmlsec(current_time) - philo_d->start, 1);
	high_priority_exit(philo_d->shared);
}

void	monitor_philos(t_philo *philo_d, t_data *data)
{
	t_time	current_time;
	int		exit_i;
	int		i;

	i = 0;
	exit_i = 0;
	if (data->num_philos == 1)
		single_philo(philo_d, &current_time, data->die);
	while (exit_i != data->num_philos - 1)
	{
		gettimeofday(&current_time, NULL);
		pthread_mutex_lock(data->meal_mutexes + i);
		if (philo_d[i].id == -2)
			exit_i++;
		else
			exit_i = 0;
		if (philo_d[i].id != -2 && \
			compare_time(&current_time, &philo_d[i].lastmeal) > data->die)
			return (print_death(philo_d + i, data, &current_time));
		pthread_mutex_unlock(data->meal_mutexes + i);
		i++;
		if (i == data->num_philos - 1)
			i = 0;
	}
}

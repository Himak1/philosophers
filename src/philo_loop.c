/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/14 14:18:23 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	print_log(pthread_mutex_t *mic, long time
					const char *message, int id)
{
	pthread_mutex_lock(mic);
	printf("%ld %d %s\n", time, id, message);
	pthread_mutex_unlock(mic);
}

static int	p_eat(t_data *data)
{

}

/*
static int	p_sleep()
{
	
}

static int	p_think
*/

void	*philo_loop(void *data)
{
	t_philo	philo;
	//int		t_sitrep; // will be used to check whether a philosopher has died
	int		state;

	gettimeofday(&philo.start, NULL);
	data = 0;
	data++;
	state = 0;
	//t_sitrep = 0;
	while (1)
	{
		
		sleep(1);
	}
}

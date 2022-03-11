/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/11 15:54:21 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

/*
static int	eat(t_data *data)
{
	
}

static int	sleep()
{
	
}
*/

void	*philo_loop(void *data)
{
	t_philo	philo;
	//int		t_sitrep;
	//int		state;

	gettimeofday(&philo.start, NULL);
	data = 0;
	data++;
	//state = 0;
	//t_sitrep = 0;
	while (1)
	{
		gettimeofday(&philo.cur_time, NULL);
		printf("%ld\n", get_thread_age(&philo));
		sleep(1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:03:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/10 16:09:45 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	eat(t_data *data)
{
	
}

static int	sleep()
{
	
}

void	*philo_loop(t_data *data)
{
	struct timeval	time;
	int				t_sitrep;
	int				state;

	state = 0;
	t_sitrep = 0;
	while (1)
	{
		gettimeofday(&time, NULL);
		printf("time: %d\n", time.tv_sec);
		if (state == 1)
			eat(data);
		else if (state == 2)
			sleep(data);
		else if (state == 3)
			think(data);
		else
			break ;
		sleep(1);
	}
}

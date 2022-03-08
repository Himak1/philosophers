/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:08:17 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/08 18:07:17 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	pthread_t	*threads;

	if (get_parameters(&data, argc, argv) == -1)
		return (1);
	data.forks = ini_mutexs(data.philos);
	if (!data.forks)
		return (1);
	if (run_threads(&data) == -1)
	{
		free(data.forks);
		return (-1);
	}
	free(data.forks);
	return (0);
}

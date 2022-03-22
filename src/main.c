/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:08:17 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/22 16:17:35 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "input.h"
#include "philo.h"

static int	too_few_args(void)
{
	write(STDERR_FILENO, "Wrong number of arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data		data;

	if (get_parameters(&data, argc, argv) == -1)
		return (too_few_args());
	data.forks = init_mutexes(data.num_philos);
	if (!data.forks)
		return (1);
	if (run_threads(&data) == -1)
	{
		free(data.forks);
		return (-1);
	}
	cleanup_mutexes(&data);
	free(data.forks);
	return (0);
}

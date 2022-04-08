/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:08:17 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/29 13:07:25 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "input.h"
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		data;

	if (get_parameters(&data, argc, argv) == -1)
		return (1);
	if (init_mutexes(&data) == -1)
		return (1);
	if (run_threads(&data) == -1)
	{
		free(data.forks);
		return (1);
	}
	cleanup_mutexes(&data);
	return (0);
}

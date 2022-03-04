/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:08:17 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/04 22:04:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "input.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (get_parameters(&data, argc, argv) == -1)
		return (-1);
	return (0);
}
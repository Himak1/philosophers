/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:08:17 by zaiba         #+#    #+#                 */
/*   Updated: 2022/02/22 16:13:44 by zaiba         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/ft_atoi.h"

int	main(int argc, char *argvp[])
{
	int	a;

	a = ft_atoi("100");
	printf("%d\n", a);
	return (0);
}
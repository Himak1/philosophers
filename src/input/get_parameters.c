/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_parameters.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 21:46:30 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/08 11:46:08 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "input.h"

static int	valid_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (isnum_str(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	overflow_error(t_data *data, int argc, char *argv[])
{
	int	status;

	status = 0;
	status += ft_sfatoi(argv[1], &data->philos);
	status += ft_sfatoi(argv[2], &data->die);
	status += ft_sfatoi(argv[3], &data->eat);
	status += ft_sfatoi(argv[4], &data->sleep);
	if (argc == 6)
		status += ft_sfatoi(argv[5], &data->num_eat);
	if (status)
	{
		write(STDERR_FILENO, "arguments must be within integer limits\n", 40);
		return (-1);
	}
	else
		return (0);
}

static int	arg_inrange(t_data *data, int argc)
{
	if (data->philos < 1
		|| data->die < 1
		|| data->eat < 1
		||data->sleep < 1)
		return (-1);
	if (argc == 6 && data->num_eat < 1)
		return (-1);
	return (0);
}

int	get_parameters(t_data *data, int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		if (valid_args(argc, argv))
		{
			write(STDERR_FILENO, "arguments must be numbers\n", 26);
			return (-1);
		}
		if (overflow_error(data, argc, argv))
			return (-1);
		if (arg_inrange(data, argc))
			return (-1);
		return (0);
	}
	return (-1);
}
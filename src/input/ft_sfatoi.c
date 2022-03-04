/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sfatoi.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 12:36:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/04 17:59:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	isnum_str(const char *str)
{
	int	i;
	int	negative;

	i = 0;
	negative = 0;
	if (str[i] == '-')
	{
		negative = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	if (i == 1 && negative == 1)
		return (-1);
	else if (i == 0)
		return (-1);
	return (0);
}

int	ft_sfatoi(const char *str, int *int_to_set)
{
	int		i;
	long	temp;
	long	ret;

	i = 0;
	ret = 0;
	temp = 0;
	if (isnum_str(str) == -1)
		return (-1);
	if (str[i] == '-')
	{
		temp = 1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		ret = (ret * 10) + str[i] - '0';
		if ((ret > MININT_INV && temp == 1) || ret > MAXINT && temp == 0)
			return (-1);
		i++;
	}
	if (temp == 1)
		ret *= -1;
	*int_to_set = ret;
	return (0);
}

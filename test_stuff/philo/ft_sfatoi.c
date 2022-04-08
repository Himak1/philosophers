/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sfatoi.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 12:36:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/11 15:37:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_sfatoi(const char *str, int *int_to_set)
{
	int		i;
	long	temp;
	long	ret;

	i = 0;
	ret = 0;
	temp = 0;
	if (str[i] == '-')
	{
		temp = 1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		ret = (ret * 10) + str[i] - '0';
		if ((ret > MININT_INV && temp == 1) || (ret > MAXINT && temp == 0))
			return (-1);
		i++;
	}
	if (temp == 1)
		ret *= -1;
	*int_to_set = ret;
	return (0);
}

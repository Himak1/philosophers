/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 12:36:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/02/24 15:29:43 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int	ft_atoi(const char *nptr)
{
	int	i;
	int	temp;
	int	ret;

	i = 0;
	ret = 0;
	temp = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			temp = 1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ret *= 10;
		ret += nptr[i] - '0';
		i++;
	}
	if (temp == 1)
		return (ret * -1);
	return (ret);
}

int	ft_sfatoi(const char *str, int *int_to_set)
{
	int	i;
	int	temp;
	int	ret;

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
		// check if value isn't too big
		ret = (ret * 10) + str[i] - '0';
		i++;
	}
	if (temp == 1)
		ret *= -1;
	*int_to_set = ret;
	return (0);
}

int	main(void)
{
	int	i;

	printf("%d\n", ft_sfatoi("414", &i));
	printf("value: %d\n", i);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:43:27 by zaiba         #+#    #+#                 */
/*   Updated: 2022/02/22 15:43:44 by zaiba         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (nptr[i] == 45 || nptr[i] == '+')
	{
		if (nptr[i] == 45)
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
	else
		return (ret);
}

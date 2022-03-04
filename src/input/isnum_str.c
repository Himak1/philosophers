/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   isnum_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 22:09:15 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/04 22:10:13 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	isnum_str(const char *str)
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

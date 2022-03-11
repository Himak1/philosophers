/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 16:05:14 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/11 14:22:07 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# define MAXINT 2147483647
# define MININT_INV 2147483648
# include "philo.h"

int	get_parameters(t_data *data, int argc, char *argv[]);

int	ft_sfatoi(const char *str, int *int_to_set);
int	isnum_str(const char *str);

#endif

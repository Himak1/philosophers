/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 15:54:07 by jhille        #+#    #+#                 */
/*   Updated: 2022/04/06 16:04:43 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// print_log returns abort_status, which can only be 0 r 2

int	print_log(t_philo *philo_d, const char *message)
{
	int	ret;

	ret = 0;
	low_priority_gate(philo_d->shared);
	if (philo_d->shared->abort != CASUALTIES)
		printf("%ld %d %s\n", get_thread_age(philo_d), philo_d->id, message);
	else
		ret = CASUALTIES;
	low_priority_exit(philo_d->shared);
	return (ret);
}

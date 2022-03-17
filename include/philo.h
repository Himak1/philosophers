/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 18:21:05 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/17 12:35:00 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				num_philos;
	int				die;
	int				eat;
	int				sleep;
	int				num_eat;
	int				abort;
	pthread_mutex_t	abort_lock;
	pthread_mutex_t	mic;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	struct timeval	cur_time;
	struct timeval	start;
	struct timeval	lastmeal;
	t_data			*shared;
}					t_philo;

pthread_mutex_t	*init_mutexes(int philos);
int				run_threads(t_data *data);

void			safesleep(long sleepquota);
long			get_thread_age(t_philo *philo);

void			*philo_loop(void *data);

#endif

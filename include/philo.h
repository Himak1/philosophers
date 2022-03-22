/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 18:21:05 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/22 16:26:36 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define THINK 0
# define EAT 1
# define SLEEP 2
# define STARVED 3
# define CASUALTIES 4
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
void			cleanup_mutexes(t_data *data);

int				run_threads(t_data *data);

int				amidead(t_philo *philo_d);
int				isanyonedead(t_philo *philo_d);

int				safesleep(t_philo *philo_d, long sleepquota);
long			get_thread_age(t_philo *philo);

int				print_log(t_philo *philo_d, long time, const char *message);

void			*philo_loop(void *data);

#endif

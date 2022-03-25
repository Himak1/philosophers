/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 18:21:05 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/25 13:35:21 by jhille        ########   odam.nl         */
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
	pthread_mutex_t	*lhm_gates;
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

//pthread_mutex_t	*init_mutexes(int philos);
int				init_mutexes(t_data *data);
void			cleanup_mutexes(t_data *data);

int				run_threads(t_data *data);

int				amidead(t_philo *philo_d);
int				isanyonedead(t_philo *philo_d);

int				safesleep(t_philo *philo_d, long sleepquota);
long			get_thread_age(t_philo *philo);

void			low_priority_gate(t_data *data);
void			low_priority_exit(t_data *data);
void			high_priority_gate(t_data *data);
void			high_priority_exit(t_data *data);

int				print_log(t_philo *philo_d, const char *message);
int				print_death(t_philo *philo_d);

void			*philo_loop(void *data);

#endif

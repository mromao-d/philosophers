#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// actions
#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINKING "is thinking"
#define DEAD "is dead"

typedef struct s_phio
{
	pthread_t		phi_t;

	int				phi_id;
	u_int64_t		t_before_d;
	int				eat_count;
	int				is_dead;
	int				eating;

	pthread_mutex_t	lock;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct s_props	*props;
}	t_philo;

typedef struct s_props
{
	u_int64_t		start_time;
	int				nb_philos;
	u_int64_t		t_before_d;
	u_int64_t		tte;
	u_int64_t		tts;
	int				is_dead;

	int				eat_all;
	pthread_mutex_t	eat_mutex;

	pthread_t		*phi_t_id;
	pthread_mutex_t	log;
	pthread_mutex_t	*forks;

	t_philo			*philo;
}	t_props;

// inits.c
int ft_init_props(t_props *props, char **argv);
int	ft_init_threads(t_props *props);

// args.c
int	ft_val_args(int argc, char **argv);
void	ft_print_philos(t_props *props);

// time.c
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

// logs
void	ft_log(t_philo *philo, char *log);
void	ft_eat(t_philo *philo);

// threads
void	*ft_routine(void	*in_philo);
void	*ft_routine_i(void	*in_nb);

// utils
long	ft_atol(const char *str);
void	ft_exit(t_props *props);

#endif

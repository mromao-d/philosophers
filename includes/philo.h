/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:43 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:19:51 by mromao-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

// actions
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_philo
{
	pthread_t		phi_t;

	int				phi_id;
	int				eat_count;
	int				is_dead;
	int				eating;

	time_t			last_meal;

	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct s_props	*props;
}	t_philo;

typedef struct s_props
{
	time_t		start_time;
	int			nb_philos;
	time_t		t_before_d;
	time_t		tte;
	time_t		tts;

	int				is_dead;
	int				thend;
	int				nb_meals;
	int				eat_all;

	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*end_lock;
	pthread_mutex_t	*log;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*nb_meals_lock;

	t_philo			*philo;
}	t_props;

// args.c
int		ft_val_args(int argc, char **argv);
// void	ft_print_philos(t_props *props);

// inits.c
int		ft_init_props(t_props *props, char **argv, int argc);
int		ft_init_threads(t_props *props);

// time.c
time_t	get_current_time(void);

// logs
void	ft_log(t_philo *philo, char *log);
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_lock_forks(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_check_end(t_philo *philo);

// threads
void	*ft_routine(void	*in_philo);
void	*ft_routine_i(void	*in_nb);
void	ft_supervisor(t_props *props);

// utils
long		ft_atol(const char *str);
void		ft_exit(t_props *props);
int			ft_strcmp(char *s1, char *s2);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strlen(char *str);
int			ft_check_dead(t_props *props);
int			th_error(char *log, char *funct);

// main
int		main(int argc, char **argv);
int		ft_one_philo(t_props *props);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:28 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:29:37 by mromao-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// eat -> think -> sleep

// ARGS
// nb_philos
// time to die
// time to eat -> time philo takes to eat
// time to sleep -> after eating
// number each philo must eat (optional)

// initiates fork mutexes. returns 0 if everythong is ok
int	ft_init_forks(t_props *props)
{
	int	i;

	i = -1;
	while (++i < props->nb_philos)
	{
		if (pthread_mutex_init(&props->forks[i], NULL) != 0)
			return (th_error("init forks", "ft_create_forks"));
	}
	return (0);
}

// Assigns forks to each philosofer
void	ft_assign_forks(t_philo *philo)
{
	if (philo->props->nb_philos == 1)
	{
		philo->left_f = &philo->props->forks[0];
		philo->right_f = &philo->props->forks[0];
		return ;
	}
	if (philo->phi_id % 2)
	{
		philo->left_f = &philo->props->forks[philo->phi_id];
		philo->right_f = &philo->props->forks[(philo->phi_id + 1)
			% philo->props->nb_philos];
	}
	else
	{
		philo->left_f = &philo->props->forks[(philo->phi_id + 1)
			% philo->props->nb_philos];
		philo->right_f = &philo->props->forks[philo->phi_id];
	}
}

// inits philos
// returns 0 if ok
// have to add time to the start time to start at moment zero.
// It will be compensated on the routine
int	ft_init_philos(t_props *props)
{
	int	i;

	i = -1;
	props->start_time = get_current_time() + (props->nb_philos * 2);
	while (++i < props->nb_philos)
	{
		props->philo[i].phi_id = i;
		props->philo[i].eat_count = 0;
		props->philo[i].is_dead = 0;
		props->philo[i].eating = 0;
		props->philo[i].last_meal = props->start_time;
		props->philo[i].props = props;
		ft_assign_forks(&props->philo[i]);
		if (pthread_create(&props->philo[i].phi_t, NULL, ft_routine, &props->philo[i]) != 0)
			return (th_error("Error creating phi_t", "ft_init_philos"));
		usleep(900);
	}
	if (props->nb_philos > 1)
		ft_supervisor(props);
	return (0);
}

// assignes args (props) to each philosofer
// matches philos with props
// returns 0 if everything is ok
// it also inits the threads
int	ft_init_props(t_props *props, char **argv, int argc)
{
	props->nb_meals = -1;
	props->nb_philos = ft_atol(argv[1]);
	props->t_before_d = ft_atol(argv[2]);
	props->tte = ft_atol(argv[3]);
	props->tts = ft_atol(argv[4]);
	if (argc == 6)
		props->nb_meals = ft_atol(argv[5]);
	props->is_dead = 0;
	props->thend = 0;
	props->dead_lock = malloc(props->nb_philos * sizeof(pthread_mutex_t));
	props->end_lock = malloc(props->nb_philos * sizeof(pthread_mutex_t));
	props->log = malloc(props->nb_philos * sizeof(pthread_mutex_t));
	props->forks = malloc(props->nb_philos * sizeof(pthread_mutex_t));
	props->nb_meals_lock = malloc(props->nb_philos * sizeof(pthread_mutex_t));
	props->philo = malloc(props->nb_philos * sizeof(t_philo));
	pthread_mutex_init(props->dead_lock, NULL);
	pthread_mutex_init(props->end_lock, NULL);
	pthread_mutex_init(props->log, NULL);
	pthread_mutex_init(props->nb_meals_lock, NULL);
	if (ft_init_forks(props))
		ft_exit(props);
	if (ft_init_philos(props))
		ft_exit(props);
	return (1);
}

// void	*ft_dead_monitor(void	*in_philo)
// {
// 	t_philo *philo;

// 	philo = (t_philo *) in_philo;
// 	// printf("%zu\n", get_current_time());
// 	// printf("%llu\n", philo->t_before_d);
// 	while (philo->props->is_dead == 0)
// 	{
// 		if (get_current_time() >= philo->t_before_d && philo->eating == 0)
// 		{
// 			philo->props->is_dead = 1;
// 			ft_log(philo, DEAD);
// 		}
// 	}
// 	// printf("here from dead\n");
// 	return (NULL);
// }

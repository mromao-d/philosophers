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

#include "philo.h"

// eat -> think -> sleep

// ARGS
// nb_philos
// time to die
// time to eat -> time philo takes to eat
// time to sleep -> after eating
// number each philo must eat (optional)

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
// returns 1 if ok
int	ft_init_philos(t_props *props)
{
	int	i;

	i = -1;
	while (++i < props->nb_philos)
	{
		props->philo[i].phi_id = i + 1;
		props->philo[i].eat_count = 0;
		props->philo[i].is_dead = 0;
		props->philo[i].eating = 0;
		pthread_mutex_init(&props->philo[i].lock, NULL);
		pthread_mutex_init(&props->forks[i], NULL);
		// if (props->nb_philos > 1)
		// 	props->philo[i].right_f = &props->forks[i - 1];
		// props->philo[i].left_f = &props->forks[i];
		props->philo[i].props = props;
		ft_assign_forks(&props->philo[i]);
	}
	return (1);
}

// assignes args (props) to each philosofer
// matches philos with props
// returns 1 if everything is ok
// it also inits the threads
int	ft_init_props(t_props *props, char **argv)
{
	props->nb_philos = ft_atol(argv[1]);
	props->start_time = get_current_time();
	props->t_before_d = ft_atol(argv[2]);
	props->tte = ft_atol(argv[3]);
	props->tts = ft_atol(argv[4]);
	props->is_dead = 0;
	props->forks = malloc(props->nb_philos * sizeof(pthread_mutex_t));
	if (!(props->forks))
		return (0);
	props->philo = malloc(props->nb_philos * sizeof(t_philo));
	if (!(props->philo))
		return (0);
	pthread_mutex_init(&props->dead_lock, NULL);
	ft_init_philos(props);
	pthread_mutex_init(&props->log, NULL);
	if (props->nb_philos == 1)
		return (ft_one_philo(props));
	ft_init_threads(props);
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

int	th_error(char *log, char *funct)
{
	printf("%s on function %s\n", log, funct);
	return (1);
}

// need sleep, otherwise the threads will not be created in order
// validate if have to increment the wait period
int	ft_init_threads(t_props *props)
{
	int			i;

	i = -1;
	// props->start_time = get_current_time();
	while (++i < props->nb_philos)
	{
		if (pthread_create(&props->philo[i].phi_t, NULL, \
			&ft_routine, &props->philo[i]))
			return (th_error("Error initializing threads", "ft_init_threads"));
		usleep(900);
	}
	i = -1;
	while (++i < props->nb_philos)
	{
		if (pthread_join(props->philo[i].phi_t, NULL))
		{
			printf("Error init_threads on philo_t_id %d", \
				props->philo[i].phi_id);
			return (0);
		}
	}
	return (1);
}

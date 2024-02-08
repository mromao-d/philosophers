/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:28 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/06 16:09:09 by mromao-d         ###   ########.fr       */
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
		pthread_mutex_init(&props->forks[i], NULL);
		props->philo[i].left_f = &props->forks[i];
		props->philo[i].right_f = &props->forks[i - 1];
		props->philo[i].props = props;
		pthread_mutex_init(&props->philo[i].lock, NULL);
	}
	props->philo[0].left_f = &props->forks[0];
	props->philo[0].right_f = &props->forks[props->nb_philos - 1];
	return (1);
}

// in case there is only one philo, I dont need both structures to have threads
// a thread can be joined or detached --> needed to 
// 		reclaim the storage space when the thread terminates
// returns 1 if everythong is ok
int	ft_one_philo(t_props *props)
{
	props->start_time = get_current_time();
	if (pthread_create(&props->phi_t_id[0], NULL, \
		&ft_routine, &props->philo[0]))
	{
		printf("Error creating thread on ft_one_philo\n");
		return (0);
	}
	pthread_detach(props->phi_t_id[0]);
	while (!props->is_dead)
		ft_usleep(0);
	return (1);
}

// assignes args (props) to each philosofer
// matches philos with props
// returns 1 if everything is ok
// it also inits the threads
int	ft_init_props(t_props *props, char **argv)
{
	props->nb_philos = atoi(argv[1]);
	props->start_time = get_current_time();
	props->t_before_d = atoi(argv[2]);
	props->tte = atoi(argv[3]);
	props->tts = atoi(argv[4]);
	props->phi_t_id = calloc(props->nb_philos, sizeof(pthread_t));
	if (!(props->phi_t_id))
		return (0);
	props->forks = calloc(props->nb_philos, sizeof(pthread_mutex_t));
	if (!(props->forks))
		return (0);
	props->philo = calloc(props->nb_philos, sizeof(t_philo *));
	if (!(props->philo))
		return (0);
	ft_init_philos(props);
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
	props->start_time = get_current_time();
	while (++i < props->nb_philos)
	{
		if (pthread_create(&props->phi_t_id[i], NULL, \
			&ft_routine, (void *) &props->philo[i]))
			return (th_error("Error initializing threads", "ft_init_threads"));
		ft_usleep(1);
	}
	i = -1;
	while (++i < props->nb_philos)
	{
		if (pthread_join(props->phi_t_id[i], NULL))
		{
			printf("Error init_threads on philo_t_id %d", \
				props->philo[i].phi_id);
			return (0);
		}
	}
	return (1);
}

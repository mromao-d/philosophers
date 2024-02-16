/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:46 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:24:06 by mromao-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// eat -> think -> sleep

// args
// nb_philos
// time to die
// time to eat -> time philo takes to eat
// time to sleep -> after eating
// number each philo must eat (optional)

// Thread é uma forma como um processo/tarefa de um programa de 
// computador é divido em duas ou mais tarefas que podem ser 
// executadas concorrentemente.

// change any state.
// format: <timestmp_in_ms> <phi_id> <action>

static void	ft_thend(t_props *props)
{
	pthread_mutex_lock(props->end_lock);
	props->thend = 1;
	pthread_mutex_unlock(props->end_lock);
}

void	ft_one_philo_new(t_props *props)
{
	ft_lock_forks(&props->philo[0]);
	usleep(props->t_before_d * 1000);
	pthread_mutex_unlock(props->philo[0].left_f);
	ft_log(&props->philo[0], DEAD);
}

// returns 1 if some philo has reached the nb of meals
static int	ft_is_last_meal(t_props *props)
{
	int	i;

	i = -1;
	while (++i < props->nb_philos)
	{
		pthread_mutex_lock(props->nb_meals_lock);
		if (props->philo[i].eat_count < props->nb_meals)
		{
			pthread_mutex_unlock(props->nb_meals_lock);
			return (0);
		}
		pthread_mutex_unlock(props->nb_meals_lock);
	}
	return (1);
}

// valdiates if it should stop due to reaching nb of meals
void	ft_supervisor(t_props *props)
{
	while (1)
	{
		if (ft_check_dead(props) == 1)
		{
			break ;
		}
		if (props->nb_meals == -1)
			continue ;
		if (ft_is_last_meal(props))
		{
			ft_thend(props);
			break ;
		}
	}
}

		// printf("here\n");
// I need to give the t_before_d here otherwise this will be poop
void	*ft_routine(void	*in_philo)
{
	t_philo	*philo;
	time_t	wait;

	philo = (t_philo *) in_philo;
	wait = philo->props->start_time - get_current_time();
	if (wait > 0)
		usleep(wait * 1000);
	if (philo->props->nb_philos == 1)
	{
		ft_one_philo_new(philo->props);
		return (NULL);
	}
	if (philo->phi_id % 2 == 0)
		ft_think(philo);
	while (!ft_check_end(philo))
	{
		ft_lock_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

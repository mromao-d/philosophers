/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:31 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:30:45 by mromao-d         ###   ########.fr       */
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

// validates if end has been reached.
// returns 1 if true
int	ft_check_end(t_philo *philo)
{
	pthread_mutex_lock(philo->props->end_lock);
	if (philo->props->thend == 1)
	{
		pthread_mutex_unlock(philo->props->end_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->props->end_lock);
	return (0);
}

void	ft_log(t_philo *philo, char *log)
{
	if (ft_check_end(philo) == 1)
		return ;
	pthread_mutex_lock(philo->props->log);
	printf("%ld philo %d %s\n", \
		get_current_time() - philo->props->start_time \
			, philo->phi_id + 1, log);
	pthread_mutex_unlock(philo->props->log);
	return ;
}

// I want them to start doing somthing
// if they are not the first to eat
void	ft_think(t_philo *philo)
{
	time_t	ttt;

	ttt = philo->props->t_before_d - (get_current_time() - philo->last_meal - philo->props->tte) / 2;
	if (ttt < 0)
		ttt = 0;
	if (ttt == 0)
		ttt = 1;
	if (ttt > 600)
		ttt = 200;
	ft_log(philo, THINKING);
	usleep(ttt * 1000);
}

void	ft_lock_forks(t_philo *philo)
{
	if (philo->props->nb_philos == 1)
	{
		pthread_mutex_lock(philo->left_f);
		ft_log(philo, FORK);
		return ;
	}
	if (philo->props->nb_philos > 1)
	{
		if (pthread_mutex_lock(philo->left_f) != 0)
			printf("Error locking left fork\n");
		ft_log(philo, FORK);
		if (pthread_mutex_lock(philo->right_f) != 0)
			printf("Error locking right fork\n");
		ft_log(philo, FORK);
	}
	return ;
}

void	ft_add_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->props->dead_lock);
	philo->last_meal = get_current_time() - philo->props->start_time;
	pthread_mutex_unlock(philo->props->dead_lock);
	pthread_mutex_lock(philo->props->nb_meals_lock);
	philo->eat_count++;
	pthread_mutex_unlock(philo->props->nb_meals_lock);
}

// takes all eating actions - locks forks, logs that shit, sleeps while eating
// unlocks forks, sleeps through sleep time
// might be needed to add a lock to the philo, have to test it
void	ft_eat(t_philo *philo)
{
	ft_add_meals(philo);
	ft_log(philo, EAT);
	usleep(philo->props->tte * 1000);
	if (philo->phi_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
	else
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
	return ;
}

void	ft_sleep(t_philo *philo)
{
	ft_log(philo, SLEEP);
	usleep(philo->props->tts * 1000);
}

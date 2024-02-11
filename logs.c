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

#include "philo.h"

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
void	ft_log(t_philo *philo, char *log)
{
	size_t	now;

	pthread_mutex_lock(&philo->props->log);
	now = get_current_time();
	if (ft_strcmp(DEAD, log) == 0 && philo->props->is_dead == 0)
	{
		printf("%llu philo %d %s\n", \
			(long long)now - (long long)philo->props->start_time \
				, philo->phi_id, log);
		philo->props->is_dead = 1;
	}
	if (philo->props->is_dead == 0)
		printf("%llu philo %d %s\n", \
		(long long)now - (long long)philo->props->start_time, \
			philo->phi_id, log);
	pthread_mutex_unlock(&philo->props->log);
	return ;
}

void	ft_forks(t_philo *philo)
{
	if (philo->props->nb_philos > 1)
	{
		pthread_mutex_lock(philo->right_f);
		ft_log(philo, FORK);
		pthread_mutex_lock(philo->left_f);
	}
	ft_log(philo, FORK);
}

void	ft_eat_utils(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->t_before_d = get_current_time() + philo->props->t_before_d;
	ft_log(philo, EAT);
	ft_usleep(philo->props->tte);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
}

// takes all eating actions - locks forks, logs that shit, sleeps while eating
// unlocks forks, sleeps through sleep time
// might be needed to add a lock to the philo, have to test it
void	ft_eat(t_philo *philo)
{
	ft_forks(philo);
	ft_eat_utils(philo);
	if (philo->props->nb_philos > 1)
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
	ft_log(philo, SLEEP);
	ft_usleep(philo->props->tts);
	return ;
}

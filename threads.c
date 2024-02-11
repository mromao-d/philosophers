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

// locks philos (needed because they are being requested 
// at the same time by the eat function and sheet)
// --> of course it happens for each and every single one of them
void	*ft_dead(void *in_philo)
{
	t_philo	*philo;

	philo = (t_philo *) in_philo;
	while (!(philo->props->is_dead))
	{
		pthread_mutex_lock(&philo->lock);
		if (get_current_time() >= philo->t_before_d && philo->eating == 0)
			ft_log(philo, DEAD);
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

// int	ft_check_dead_old(t_philo *philo)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < philo->props->nb_philos)
// 	{
// 		if(philo->props->is_dead == 1)
// 			return (1);
// 		if (get_current_time() >= philo->t_before_d && philo->eating == 0)
// 		{
// 			ft_log(philo, DEAD);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int	ft_check_dead(t_philo *philo)
{
	if (philo->props->is_dead == 1)
		return (1);
	if (get_current_time() >= philo->t_before_d && philo->eating == 0)
	{
		ft_log(philo, DEAD);
		return (1);
	}
	return (0);
}

		// printf("here\n");
// I need to give the t_before_d here otherwise this will be poop
void	*ft_routine(void	*in_philo)
{
	t_philo	*philo;

	philo = (t_philo *) in_philo;
	philo->t_before_d = philo->props->t_before_d + get_current_time();
	while (!ft_check_dead(philo))
	{
		ft_eat(philo);
		ft_log(philo, THINKING);
	}
	return (NULL);
}

		// printf("here\n");
// I need to give the t_before_d here otherwise this will be poop
// void	*ft_routine_old(void	*in_philo)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) in_philo;
// 	philo->t_before_d = philo->props->t_before_d + get_current_time();
// 	if (pthread_create(&philo->phi_t, NULL, &ft_dead, (void *) philo))
// 	{
// 		printf("Error ft_routine\n");
// 		return ((void *)1);
// 	}
// 	while (!philo->props->is_dead)
// 	{
// 		ft_eat(philo);
// 		ft_log(philo, THINKING);
// 	}
// 	if (pthread_join(philo->phi_t, NULL))
// 		return ((void *) 1);
// 	return (NULL);
// }

void	*ft_routine_i(void	*in_nb)
{
	int	*i;

	i = (int *) in_nb;
	printf("Here with filo %d\n", *i);
	return (NULL);
}

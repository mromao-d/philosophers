/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:53 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:21:11 by mromao-d         ###   ########.fr       */
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

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'\
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (str[i] == ' ')
			i++;
		else
		{
			result = result * 10 + str[i] - 48;
			i++;
		}
	}
	return (result * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 == *s2) && *s1)
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

// validates if someone is dead. Returns 2 if yes
// returns 0 if is alive
int	ft_check_dead(t_props *props)
{
	int		i;

	i = -1;
	while (++i < props->nb_philos)
	{
		pthread_mutex_lock(props->dead_lock);
		if ((get_current_time() - props->start_time - props->philo[i].last_meal) >= props->t_before_d)
		{
			ft_log(&props->philo[i], DEAD);
			pthread_mutex_lock(props->end_lock);
			props->thend = 1;
			pthread_mutex_unlock(props->end_lock);
			pthread_mutex_unlock(props->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(props->dead_lock);
	}
	// printf("here from check dead\n");
	return (0);
}

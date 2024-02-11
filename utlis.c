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

void	ft_free_data(t_props *props)
{
	if (props->forks)
		free(props->forks);
	if (props->philo)
		free(props->philo);
	return ;
}

void	ft_exit(t_props *props)
{
	int	i;

	i = -1;
	while (++i < props->nb_philos)
	{
		pthread_mutex_destroy(&props->forks[i]);
		pthread_mutex_destroy(&props->philo[i].lock);
	}
	pthread_mutex_destroy(&props->log);
	pthread_mutex_destroy(&props->dead_lock);
	return (ft_free_data(props));
}

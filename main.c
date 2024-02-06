/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:35 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/06 15:52:00 by mromao-d         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_props	*props;

	if (!ft_val_args(argc, argv))
		return (1);
	props = calloc(sizeof(t_props), 1);
	if (!props)
		return (2);
	if (!ft_init_props(props, argv))
	{
		printf("Failed to init props\n");
		return (3);
	}
	return (0);
}

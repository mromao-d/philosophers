/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:35 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:08:32 by mromao-d         ###   ########.fr       */
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

// in case there is only one philo, I dont need both structures to have threads
// returns 1 if everythong is ok
// int	ft_one_philo(t_props *props)
// {
// 	props->philo[0].t_before_d = props->t_before_d + get_current_time();
// 	while (!ft_check_dead(&props->philo[0]))
// 		ft_eat(&props->philo[0]);
// 	ft_exit(props);
// 	return (1);
// }

// join threads.
// returns 0 if everything is ok
static int	ft_join_th(t_props *props)
{
	int	i;

	i = -1;
	while (++i < props->nb_philos)
	{
		if (pthread_join(props->philo[i].phi_t, NULL))
			return (th_error("Error joining", "ft_join_th"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_props	props;

	if (ft_val_args(argc, argv))
		return (1);
	if (!ft_init_props(&props, argv, argc))
	{
		printf("Failed to init props");
		ft_exit(&props);
		return (3);
	}
	if (ft_join_th(&props))
		ft_exit(&props);
	ft_exit(&props);
	return (0);
}

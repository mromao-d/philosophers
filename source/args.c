/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:30:22 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:17:43 by mromao-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// eat -> think -> sleep

// ARGS
// nb_philos
// time to die
// time to eat -> time philo takes to eat
// time to sleep -> after eating
// number each philo must eat (optional)

// validate args are numbers
// returns 1 if shit has happened
int	ft_val_nb(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			while (argv[i][j] == ' ')
				j++;
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("shit happened on the arguments\n");
				return (1);
			}
		}
	}
	return (0);
}

// validate if arg is bigger than max int
// returns 1 if shit happened
int	ft_validate_size(char **argv)
{
	int	i;
	int	len;

	i = 0;
	while (argv[i])
	{
		len = ft_strlen(argv[i]);
		if (len > 10)
		{
			printf("Arg bigger than int\n");
			return (1);
		}
		if (len == 10 && ft_strcmp(argv[i], "2147483647") > 0)
		{
			printf("Arg bigger than int\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// validate args
// returns > 0 if shit happens
int	ft_val_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6) 
	{
		printf("Error\nInvalid number of args");
		return (1);
	}
	if (!(ft_atol(argv[1]) > 0 && ft_atol(argv[1]) < 500 ))
	{
		printf("nb of philos is bigger than 0 e lesser than 500\n");
		return (0);
	}
	return (ft_val_nb(argv) + ft_validate_size(argv));
	return (0);
}

// just to check that everything is ok
// void	ft_print_philos(t_props *props)
// {
// 	int	i;

// 	for (i = 0; i < props->nb_philos; i++)
// 		printf("Hello from philo %d\n", props->philo[i].phi_id);
// 	return ;
// }

#include "philo.h"

// eat -> think -> sleep

// ARGS
// nb_philos
// time to die
// time to eat -> time philo takes to eat
// time to sleep -> after eating
// number each philo must eat (optional)

// validate args are numbers
// returns 0 if shit has happened
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
				return (0);
			}
		}
	}
	return (1);
}

// validate args
int	ft_val_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6) 
	{
		printf("Error\nInvalid number of args");
		return (0);
	}
	return (ft_val_nb(argv));
	return (1);
}

// just to check that everything is ok
void	ft_print_philos(t_props *props)
{
	int	i;

	for (i = 0; i < props->nb_philos; i++)
		printf("Hello from philo %d\n", props->philo[i].phi_id);
	return ;
}

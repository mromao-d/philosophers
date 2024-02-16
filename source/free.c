#include "../includes/philo.h"

static void	ft_free_props(t_props *props)
{
	if (props->philo)
		free(props->philo);
	if (props->forks)
		free(props->forks);
	if (props->log)
		free(props->log);
	if (props->end_lock)
		free(props->end_lock);
	if (props->nb_meals_lock)
		free(props->nb_meals_lock);
	if (props->dead_lock)
		free(props->dead_lock);
}

static void	ft_destroy_mutexes(t_props *props)
{
	if (props->log)
		pthread_mutex_destroy(props->log);
	if (props->dead_lock)
		pthread_mutex_destroy(props->dead_lock);
	if (props->end_lock)
		pthread_mutex_destroy(props->end_lock);
	if (props->nb_meals_lock)
		pthread_mutex_destroy(props->nb_meals_lock);
}

static void ft_destroy_forks(t_props *props)
{
	int i;

	i = -1;
	while (++i < props->nb_philos)
		pthread_mutex_destroy(&props->forks[i]);
}

void    ft_exit(t_props *props)
{
	if (props)
	{
		if (props->forks)
			ft_destroy_forks(props);
		ft_destroy_mutexes(props);
		ft_free_props(props);
	}
}

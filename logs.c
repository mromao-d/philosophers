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
	size_t  now;

	pthread_mutex_lock(&philo->props->log);
	now = get_current_time();
	if (strcmp(DEAD, log) == 0 && philo->props->is_dead == 0)
	{
		printf("%llu philo %d %s\n", now - philo->props->start_time, philo->phi_id, log);
		philo->props->is_dead = 1;
	}
	if (philo->props->is_dead == 0)
		printf("%llu philo %d %s\n", now - philo->props->start_time, philo->phi_id, log);
	pthread_mutex_unlock(&philo->props->log);
	return ;
}

// takes all eating actions - locks forks, logs that shit, sleeps while eating
// unlocks forks, sleeps through sleep time
// might be needed to add a lock to the philo, have to test it
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	ft_log(philo, FORK);
	pthread_mutex_lock(philo->left_f);
	ft_log(philo, FORK);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->t_before_d = get_current_time() + philo->props->t_before_d;
	ft_log(philo, EAT);
	philo->eat_count++;
	philo->props->eat_all++;
	ft_usleep(philo->props->tte);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	ft_log(philo, SLEEP);
	ft_usleep(philo->props->tts);
	return ;
}

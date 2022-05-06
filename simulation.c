#include"philo.h"

int	get_time(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	sleeping(t_philo *philo)
{
	philo->i = 0;
	philo->j = 0;
	printf("%s%d ms: philo %d is sleeping😴\n", green, (get_time() - philo->past), philo->philo_id + 1);
	usleep(philo->sleep_time * 1000);
	printf("%s%d ms: philo %d is thinking🤔\n", purple, (get_time() - philo->past), philo->philo_id + 1);
	philo->eat_stop[philo->philo_id] += 1;
	while (philo->eat_stop[philo->i] && philo->eat_rounds != 0)
	{
		if (philo->eat_stop[philo->i] == philo->eat_rounds)
			philo->j++;
		philo->i++;
	}
	if (philo->eat_stop[philo->philo_id] == philo->eat_rounds)
	{
		pthread_detach(philo->philos);
		while(1);
	}
	if (philo->j == philo->nb_of_philos)
			exit(0);
	eating(philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	philo->flag = 0;
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d is eating🍝\n", blue, (get_time() - philo->past), philo->philo_id + 1);
	usleep(philo->eat_time * 1000);
	philo->time_round = get_time();
	philo->flag = 1;
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	sleeping(philo);
}

void	dying_timer(t_philo *philo)
{
	philo->time_round = philo->past;
	while (1)
	{
		if ((get_time() - philo->time_round) > philo->death_time && philo->flag == 1)
		{
			printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
			exit(0);
		}
	}
}

void	*dying_thread(void *ptr)
{
	t_philo	*philo;

	philo = (void *)ptr;
	dying_timer(philo);
	return (0);
}

void	*launch(void *ptr)
{
	t_philo	*philo;

	philo = (void *)ptr;
	philo->past = get_time();
	while (1)
		eating(philo);
	return (ptr);
}
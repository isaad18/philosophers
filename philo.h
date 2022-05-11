#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<strings.h>
# include<sys/time.h>
# include<stdlib.h>
# include<pthread.h>

# define black "\033[0;30m"
# define red "\033[0;31m"
# define green "\033[0;32m"
# define yellow "\033[0;33m"
# define blue "\033[0;34m"
# define purple "\033[0;35m"
# define cyan "\033[0;36m"
# define white "\033[0;37m"

typedef struct s_data
{
	int				*conditional_forks;
	int				round_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	holder;
	pthread_mutex_t	holder2;
	pthread_mutex_t	holder3;
	pthread_mutex_t	holder4;
	pthread_mutex_t	holder5;
}	t_data;

typedef struct s_philo
{
	t_data 			*data;
	int				right_fork;
	int				left_fork;
	int				philo_id;
	int				eat_rounds;
	int				eat_time;
	int				sleep_time;
	int				flag;
	int				death_time;
	int				start_time;
	int				time_round;
	int				round;
	pthread_t		death;
	pthread_t		philos;
	pthread_t		*philoss;
	int				past;
	int				time_diff;
	int				*eat_stop;
	int				nb_of_philos;
	int				i;
	int				j;
	int				x;
}		t_philo;

void	checkinput(char **argv, int i, int j);
int		pars(char **argv);
void	*launch(void *ptr);
void	eating(t_philo *philo);
void	dying_timer(t_philo *philo);
void	*dying_thread(void *ptr);

#endif

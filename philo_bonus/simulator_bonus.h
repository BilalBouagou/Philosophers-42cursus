/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:15:21 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/27 22:49:02 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATOR_BONUS_H
# define SIMULATOR_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>

# define DEATH "%lld %d has died\n"
# define THINKING "%lld %d is thinking\n"
# define SLEEPING "%lld %d is sleeping\n"
# define EATING "%lld %d is eating\n"
# define TAKING_FORKS "%lld %d has taken a fork\n"

# define TRUE 1
# define FALSE 0
# define SNAME "semaphore"
# define PNAME "p_semaphore"
# define SYNC "sync"

typedef enum s_actions
{
	FORK_TAKEN,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_actions;

struct s_philo
{
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_ate;
	int					times_philo_must_eat;
	int					set_philo_eat_time;
	long long			status;
	long long			start;
	sem_t				*sem;
	sem_t				*psem;
	sem_t				*sync;
};

typedef struct s_info
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
	int				set_philo_eat_time;
	int				chld_status;
	int				nb_child;
	long long		start;
	pid_t			*pids;
	pid_t			chld_pid;
	sem_t			*sem;
	sem_t			*psem;
	sem_t			*sync;
	struct s_philo	*philo;
}	t_info;

void		parser(char **args, int args_num, t_info *target);

int			ft_atoi(const char *str);
long long	t_time(void);
void		ft_usleep(unsigned long long time);
void		think(struct s_philo *philo);
void		eat(struct s_philo *philo);
void		ph_sleep(struct s_philo *philo);
void		kill_them_all(t_info *info);
void		announcer(struct s_philo *philo, t_actions action);

#endif
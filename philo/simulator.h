/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 05:24:49 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/07 23:21:20 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATOR_H

# define SIMULATOR_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define DEATH "%lld %d died\n"
# define TAKING_FORKS "%lld %d has taken a fork\n"
# define EATING "%lld %d is eating\n"
# define SLEEPING "%lld %d is sleeping\n"
# define THINKING "%lld %d is thinking\n"

# define TRUE 1
# define FALSE 0

/*
 * STRUCTS DEFINITIONS
 * */

typedef enum e_actions
{
	FORK_TAKEN,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_actions;

struct s_info
{
	int					id;
	int					t_eat;
	int					t_sleep;
	int					t_die;
	int					times_ate;
	long long			last_meal;
	long long			start;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*print;
};

typedef struct s_philo
{
	int				nb_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				times_philo_must_eat;
	int				set_philo_eat_time;
	int				err;
	long long		start;
	struct s_info	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_philo;

/*
 * PARSER DECLARATION
 * */

int			parser(char **args, int args_num, t_philo *target);

/*
 * HELPER FUNCTIONS
 * */

int			ft_atoi(const char *str);
long long	t_time(void);
int			monitor_philos(t_philo *info);
void		ft_usleep(unsigned long long time);
void		announcer(struct s_info *philo, t_actions action);
void		eat(struct s_info *philo);
void		ph_sleep(struct s_info *philo);
void		think(struct s_info *philo);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:13 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/09 23:04:58 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator.h"

void	announcer(struct s_info *philo, t_actions action)
{
	if (action == DIE)
		printf(DEATH, t_time() - philo->start, philo->id);
	else
	{
		pthread_mutex_lock(philo->print);
		if (action == FORK_TAKEN)
			printf(TAKING_FORKS, t_time() - philo->start, philo->id);
		else if (action == EAT)
		{
			printf(EATING, t_time() - philo->start, philo->id);
			philo->last_meal = t_time();
		}
		else if (action == SLEEP)
			printf(SLEEPING, t_time() - philo->start, philo->id);
		else if (action == THINK)
			printf(THINKING, t_time() - philo->start, philo->id);
		pthread_mutex_unlock(philo->print);
	}
}

static void	pick_fork(struct s_info *philo)
{
	pthread_mutex_lock(philo->l_fork);
	announcer(philo, FORK_TAKEN);
	pthread_mutex_lock(philo->r_fork);
	announcer(philo, FORK_TAKEN);
}

void	eat(struct s_info *philo)
{
	pick_fork(philo);
	announcer(philo, EAT);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(philo->print);
	philo->times_ate++;
	pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ph_sleep(struct s_info *philo)
{
	announcer(philo, SLEEP);
	ft_usleep(philo->t_sleep);
}

void	think(struct s_info *philo)
{
	announcer(philo, THINK);
}

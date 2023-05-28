/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:32:58 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/27 22:53:40 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator_bonus.h"

void	announcer(struct s_philo *philo, t_actions action)
{
	sem_wait(philo->psem);
	if (action == DIE)
		printf(DEATH, t_time() - philo->start, philo->id);
	else
	{
		if (action == FORK_TAKEN)
			printf(TAKING_FORKS, t_time() - philo->start, philo->id);
		else if (action == EAT)
			printf(EATING, t_time() - philo->start, philo->id);
		else if (action == SLEEP)
			printf(SLEEPING, t_time() - philo->start, philo->id);
		else if (action == THINK)
			printf(THINKING, t_time() - philo->start, philo->id);
		sem_post(philo->psem);
	}
}

void	ph_sleep(struct s_philo *philo)
{
	announcer(philo, SLEEP);
	ft_usleep(philo->time_to_sleep);
}

void	pick_forks(struct s_philo *philo)
{
	sem_wait(philo->sem);
	announcer(philo, FORK_TAKEN);
	sem_wait(philo->sem);
	announcer(philo, FORK_TAKEN);
}

void	eat(struct s_philo *philo)
{
	pick_forks(philo);
	sem_wait(philo->sync);
	philo->status = t_time();
	sem_post(philo->sync);
	announcer(philo, EAT);
	ft_usleep(philo->time_to_eat);
	sem_wait(philo->sync);
	philo->times_ate++;
	sem_post(philo->sync);
	sem_post(philo->sem);
	sem_post(philo->sem);
}

void	kill_them_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
	{
		kill(info->pids[i], SIGTERM);
		i++;
	}
}

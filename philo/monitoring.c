/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:37:29 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/28 16:04:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator.h"

static int	is_finished(t_philo *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philos)
	{
		if (info->philo[i].times_ate < info->times_philo_must_eat)
			break ;
		i++;
		if (i > info->nb_philos - 1)
			return (1);
	}
	return (0);
}

int	monitor_philos(t_philo *info)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->print);
		if (t_time() - info->philo[i].last_meal > info->t_die)
			break ;
		if (info->set_philo_eat_time)
			if (is_finished(info))
				return (0);
		pthread_mutex_unlock(&info->print);
		i++;
		if (i > info->nb_philos - 1)
		{
			if (info->t_die > 200)
				usleep(20);
			i = 0;
		}
	}
	announcer(&info->philo[i], DIE);
	return (0);
}

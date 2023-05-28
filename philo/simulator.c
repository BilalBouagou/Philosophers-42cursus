/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 05:27:16 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/28 21:00:10 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator.h"

static void	*thread_routine(void *philo)
{
	if (((struct s_info *)philo)->id % 2 == 1)
	{
		think((struct s_info *)philo);
		ft_usleep(((struct s_info *)philo)->t_eat);
	}
	while (1)
	{
		eat((struct s_info *)philo);
		ph_sleep((struct s_info *)philo);
		think((struct s_info *)philo);
	}
	return (NULL);
}

static	int	error_manager(int code)
{
	if (code == 1)
		printf("Error : Malloc error\n");
	else if (code == 2)
		printf("Error : Couldn't create a thread\n");
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	t_philo			*info;
	pthread_t		*thread_id;

	info = (t_philo *)malloc(sizeof(t_philo));
	if (!info)
		return (error_manager(1));
	if (!parser(argv, argc - 1, info))
		return (0);
	thread_id = (pthread_t *)malloc(info->nb_philos * sizeof(pthread_t));
	if (!thread_id)
		return (error_manager(1));
	i = -1;
	info->start = t_time();
	while (++i < info->nb_philos)
	{
		info->philo[i].start = info->start;
		info->philo[i].last_meal = info->start;
		info->err = pthread_create(&thread_id[i],
				NULL, thread_routine, &info->philo[i]);
		if (info->err)
			return (error_manager(2));
	}
	free (thread_id);
	return (monitor_philos(info));
}

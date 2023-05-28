/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:49:32 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/28 16:11:03 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator_bonus.h"

void	*philo_routine(void *philo)
{
	while (1)
	{
		announcer((struct s_philo *)philo, THINK);
		eat((struct s_philo *)philo);
		ph_sleep((struct s_philo *)philo);
	}
	return (NULL);
}

void	child_process(struct s_philo *philo)
{
	pthread_t	thread_id;

	philo->sem = sem_open(SNAME, 0);
	philo->psem = sem_open(PNAME, 0);
	philo->sync = sem_open(SYNC, 0);
	pthread_create(&thread_id, NULL, philo_routine, philo);
	while (1)
	{
		sem_wait(philo->sync);
		if (t_time() - philo->status > philo->time_to_die)
			break ;
		else if (philo->set_philo_eat_time
			&& philo->times_ate >= philo->times_philo_must_eat)
		{
			sem_post(philo->sync);
			exit(1);
		}
		sem_post(philo->sync);
		usleep(20);
	}
	announcer(philo, DIE);
	exit(0);
}

int	error_manager(int code)
{
	if (code == 1)
		printf("Error : Couldn't create a process.\n");
	else if (code == 2)
		printf("Error : Malloc error.\n");
	return (0);
}

void	wait_processes(t_info *info)
{
	while (info->nb_child)
	{
		info->chld_pid = waitpid(0, &info->chld_status, 0);
		info->nb_child--;
		if (info->chld_status == 0)
			return ;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_info	*info;
	pid_t	pid;
	int		i;

	sem_unlink(SNAME);
	sem_unlink(PNAME);
	sem_unlink(SYNC);
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (error_manager(2));
	parser(argv, argc - 1, info);
	i = -1;
	while (++i < info->number_of_philos)
	{
		pid = fork();
		if (!pid)
			child_process(&info->philo[i]);
		else if (pid)
			info->pids[i] = pid;
		else
			return (error_manager(1));
	}
	wait_processes(info);
	kill_them_all(info);
}

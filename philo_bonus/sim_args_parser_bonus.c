/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_args_parser_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:01:33 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/27 22:49:15 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator_bonus.h"

static void	err_message(int code, int args_num)
{
	if (!code)
		printf("Error : Incorrect number of arguments (expected 4) got %d\n",
			args_num);
	else if (code == 1)
	{
		printf("Error : All arguments must be numbers.\n");
		printf("Format : number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	else if (code == 2)
		printf("Error : None of the parameters can be less or equal to 0\n");
	else if (code == 3)
		printf("Error : The number of forks can't exceed SEM_VALUE_MAX\n");
	else if (code == 4)
		printf("Error : semaphore couldn't be created");
	else if (code == 5)
		printf("Error : Malloc error\n");
	exit (0);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static	void	initialise_data(t_info *target)
{
	int	i;

	i = -1;
	target->start = t_time();
	target->chld_status = 1;
	while (++i < target->number_of_philos)
	{
		target->philo[i].id = i + 1;
		target->philo[i].time_to_eat = target->time_to_eat;
		target->philo[i].time_to_sleep = target->time_to_sleep;
		target->philo[i].time_to_die = target->time_to_die;
		target->philo[i].times_philo_must_eat = target->times_philo_must_eat;
		target->philo[i].set_philo_eat_time = target->set_philo_eat_time;
		target->philo[i].status = target->start;
		target->philo[i].times_ate = 0;
		target->philo[i].start = target->start;
	}
}

static	void	load_info_to_struct(char **args, t_info *target)
{
	target->number_of_philos = ft_atoi(args[0]);
	target->time_to_die = ft_atoi(args[1]);
	target->time_to_eat = ft_atoi(args[2]);
	target->time_to_sleep = ft_atoi(args[3]);
	if (args[4])
	{
		target->times_philo_must_eat = ft_atoi(args[4]);
		target->set_philo_eat_time = TRUE;
	}
	else
	{
		target->times_philo_must_eat = 1;
		target->set_philo_eat_time = FALSE;
	}
	target->nb_child = target->number_of_philos;
	target->philo = (struct s_philo *) malloc(target->number_of_philos
			* sizeof(struct s_philo));
	target->pids = (pid_t *) malloc(target->number_of_philos * sizeof(pid_t));
	if (!target->philo || !target->pids)
		err_message(5, 0);
	initialise_data(&(*target));
}

void	parser(char **args, int args_num, t_info *target)
{
	int	i;
	int	j;

	if (args_num < 4 || args_num > 5)
		err_message(0, args_num);
	i = 0;
	while (++i < args_num + 1)
	{
		j = -1;
		while (args[i][++j])
			if (!ft_isdigit(args[i][j]))
				err_message(1, 0);
	}
	load_info_to_struct(args + 1, &(*target));
	if (target->times_philo_must_eat <= 0 || target->number_of_philos <= 0
		|| target->time_to_die <= 0 || target->time_to_eat <= 0
		|| target->time_to_sleep <= 0)
		err_message(2, 0);
	if (target->number_of_philos > SEM_VALUE_MAX)
		err_message(3, 0);
	target->sem = sem_open(SNAME, O_CREAT, 0644, target->number_of_philos);
	target->psem = sem_open(PNAME, O_CREAT, 0644, 1);
	target->sync = sem_open(SYNC, O_CREAT, 0644, 1);
	if (target->sem == SEM_FAILED || target->psem == SEM_FAILED)
		err_message(4, 0);
}

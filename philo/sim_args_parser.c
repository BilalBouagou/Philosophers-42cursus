/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_args_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 05:29:06 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/07 23:21:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator.h"

static int	err_message(int code, int args_num)
{
	if (!code)
		printf("Error : Incorrect number of arguments (expected 4) got %d\n",
			args_num);
	else if (code == 1)
	{
		printf("Error : All arguments must be numbers.\n");
		printf("Format : nb_philosophers t_die t_eat ");
		printf("t_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	else if (code == 2)
		printf("Error : None of the parameters can be less or equal to 0\n");
	else if (code == 3)
		printf("Error : Malloc error\n");
	return (0);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static	void	initialise_data(t_philo *target)
{
	int	i;

	i = -1;
	while (++i < target->nb_philos)
		pthread_mutex_init(&target->forks[i], NULL);
	pthread_mutex_init(&target->print, NULL);
	i = -1;
	while (++i < target->nb_philos)
	{
		target->philo[i].id = i + 1;
		if (!i)
			target->philo[i].l_fork = &target->forks[target->nb_philos - 1];
		else
			target->philo[i].l_fork = &target->forks[i - 1];
		target->philo[i].r_fork = &target->forks[i];
		target->philo[i].print = &target->print;
		target->philo[i].t_eat = target->t_eat;
		target->philo[i].t_sleep = target->t_sleep;
		target->philo[i].last_meal = 0;
		target->philo[i].times_ate = 0;
	}
}

static	void	load_info_to_struct(char **args, t_philo *target)
{
	target->nb_philos = ft_atoi(args[0]);
	target->t_die = ft_atoi(args[1]);
	target->t_eat = ft_atoi(args[2]);
	target->t_sleep = ft_atoi(args[3]);
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
	target->forks = (pthread_mutex_t *) malloc(target->nb_philos
			* (sizeof(pthread_mutex_t)));
	target->philo = (struct s_info *) malloc(target->nb_philos
			* sizeof(struct s_info));
	if (!target->forks || !target->philo)
		return ;
	initialise_data(target);
}

int	parser(char **args, int args_num, t_philo *target)
{
	int	i;
	int	j;

	if (args_num < 4 || args_num > 5)
		return (err_message(0, args_num));
	i = 0;
	while (++i < args_num + 1)
	{
		j = -1;
		while (args[i][++j])
			if (!ft_isdigit(args[i][j]))
				return (err_message(1, 0));
	}
	load_info_to_struct(args + 1, target);
	if (target->times_philo_must_eat <= 0 || target->nb_philos <= 0
		|| target->t_die <= 0 || target->t_eat <= 0
		|| target->t_sleep <= 0)
		return (err_message(2, 0));
	if (!target->forks || !target->philo)
		return (err_message(3, 0));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:07:42 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/07 23:46:15 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulator.h"

static	int	escape_whitespaces(char c)
{
	if (c == 32 || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	sign;

	j = 0;
	i = 0;
	sign = 1;
	while (escape_whitespaces(str[j]))
		j++;
	if (str[j] == '+' || str[j] == '-')
	{
		if (str[j] == '-')
			sign *= -1;
		j++;
	}
	while (ft_isdigit(str[j]))
	{
		i += str[j] - '0';
		j++;
		if (ft_isdigit(str[j]))
			i *= 10;
	}
	return (i * sign);
}

void	ft_usleep(unsigned long long time)
{
	unsigned long long	sleep;

	sleep = t_time();
	while (t_time() - sleep != time)
		usleep (200);
}

long long	t_time(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

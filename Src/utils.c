/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:04:27 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 14:40:47 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	did_you_just_die(t_philo *philo)
{
	if (get_int(philo->dead_lock, philo->dead) == 1)
		return (1);
	return (0);
}

int	is_fed(t_philo *philo)
{
	if (get_int(philo->meal_lock, &philo->eating_goal) != -1
		&& (get_int(philo->meal_lock,
				&philo->eating_goal) <= (get_int(philo->meal_lock,
					&philo->meals))))
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd > 0)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	res;
	int			signe;

	i = 0;
	res = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	res = res * signe;
	return (res);
}

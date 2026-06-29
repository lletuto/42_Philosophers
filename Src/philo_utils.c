/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:43:55 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 14:10:45 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milliseconds)
	{
		if (get_int(philo->dead_lock, philo->dead))
			return ;
		usleep(100);
	}
}

void	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

int	get_int(pthread_mutex_t *mutex, int *dest)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *dest;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_size_t(pthread_mutex_t *mutex, size_t *dest, size_t value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

size_t	get_size_t(pthread_mutex_t *mutex, size_t *dest)
{
	size_t	res;

	pthread_mutex_lock(mutex);
	res = *dest;
	pthread_mutex_unlock(mutex);
	return (res);
}

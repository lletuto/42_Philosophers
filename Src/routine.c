/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:05:52 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 14:53:31 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	size_t	wait;

	if (did_you_just_die(philo))
		return ;
	print_message("is thinking", philo);
	wait = (philo->tt_die - (philo->ate_last - get_time())) / 2;
	usleep(wait);
}

static void	sleeping(t_philo *philo)
{
	if (did_you_just_die(philo))
		return ;
	print_message("is sleeping", philo);
	if (did_you_just_die(philo))
		return ;
	ft_usleep(philo->tt_sleep, philo);
}

static void	eat(t_philo *philo)
{
	if (did_you_just_die(philo) == 1)
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	if (philo->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (ft_usleep(philo->tt_die, philo));
	}
	if (did_you_just_die(philo) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	print_message("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->ate_last = get_time();
	philo->meals++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->tt_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*run_it(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (get_int(philo->start_mutex, philo->start) == 0)
	{
		usleep(1000);
	}
	set_size_t(philo->meal_lock, &philo->ate_last, *philo->start_time);
	if (philo->name % 2 == 0)
		ft_usleep(2, philo);
	while (did_you_just_die(philo) == 0)
	{
		if (did_you_just_die(philo) == 1)
			break ;
		eat(philo);
		if (did_you_just_die(philo) == 1 || philo->nb_philo == 1)
			break ;
		sleeping(philo);
		if (did_you_just_die(philo) == 1)
			break ;
		think(philo);
	}
	return (NULL);
}

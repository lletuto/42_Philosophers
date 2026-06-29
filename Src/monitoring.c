/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:43:57 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 11:29:28 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	if (get_time() - get_size_t(philo->meal_lock,
			&philo->ate_last) >= philo->tt_die + 10)
		return (1);
	return (0);
}

static int	dead_philos(t_philo *philo)
{
	t_philo	*current;

	current = philo;
	while (current)
	{
		if (is_dead(current))
		{
			print_message("died", current);
			set_int(current->dead_lock, current->dead, 1);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	fed_philos(t_philo *philo)
{
	t_philo	*current;

	current = philo;
	while (current)
	{
		if (!is_fed(current))
			return (0);
		current = current->next;
	}
	current = philo;
	set_int(current->dead_lock, current->dead, 1);
	return (1);
}

static void	*monitoring_all(void *args)
{
	t_program	*program;

	program = (t_program *)args;
	while (1)
	{
		if (get_int(&program->start_mutex, &program->start) != 0)
			break ;
		else
			usleep(1000);
	}
	usleep(1000);
	while (1)
	{
		if (dead_philos(program->philo) == 1 || fed_philos(program->philo) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}

int	monitoring(t_program *program, pthread_t *keeper_thread)
{
	if (pthread_create(keeper_thread, NULL, monitoring_all, program) != 0)
		return (ft_putstr_fd("Failed to create thread\n", STDERR_FILENO), -1);
	usleep(1000);
	return (0);
}

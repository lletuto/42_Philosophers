/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:26:54 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 13:40:12 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	size_t	timestamp;

	if (get_int(philo->dead_lock, philo->dead) == 0)
	{
		pthread_mutex_lock(philo->write_lock);
		timestamp = get_time() - get_size_t(philo->start_mutex,
				philo->start_time);
		if (get_int(philo->dead_lock, philo->dead) != 0)
		{
			pthread_mutex_unlock(philo->write_lock);
			return ;
		}
		printf("%zu %i %s\n", timestamp, philo->name, str);
		pthread_mutex_unlock(philo->write_lock);
	}
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	free_philo(t_philo *philo)
{
	t_philo	*current;
	t_philo	*next;

	if (!philo)
		return ;
	next = philo;
	while (next)
	{
		current = next;
		next = current->next;
		free(current);
		current = NULL;
	}
}

void	free_all(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->start_mutex);
	if (!program->forks)
		return ;
	while (i < program->nb_philo)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	free(program->forks);
	program->forks = NULL;
	free_philo(program->philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:05:23 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 14:05:52 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_program_mutex(t_program *program)
{
	if (pthread_mutex_init(&program->start_mutex, NULL) != 0)
		return (ft_putstr_fd("Dead_lock mutex init failed\n", STDERR_FILENO),
			-1);
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (ft_putstr_fd("Dead_lock mutex init failed\n", STDERR_FILENO),
			-1);
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (ft_putstr_fd("Write_lock mutex init failed\n", STDERR_FILENO),
			-1);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
		return (ft_putstr_fd("Meal_lock mutex init failed\n", STDERR_FILENO),
			-1);
	return (0);
}

static void	init_given_values(t_program *program, char **argv, int argc)
{
	program->tt_die = ft_atoll(argv[2]);
	program->tt_eat = ft_atoll(argv[3]);
	program->tt_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		program->eating_goal = ft_atoll(argv[5]);
	else
		program->eating_goal = -1;
}

int	init_program(t_program *program, char **argv, int argc)
{
	int	i;

	i = 0;
	memset(program, 0, sizeof(t_program));
	program->nb_philo = ft_atoll(argv[1]);
	init_given_values(program, argv, argc);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->nb_philo);
	if (!program->forks)
		return (-1);
	while (i < program->nb_philo)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (ft_putstr_fd("Forks mutex init failed\n", STDERR_FILENO),
				-1);
		i++;
	}
	if (init_program_mutex(program) < 0)
		return (-1);
	program->start_time = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:17:04 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 15:19:36 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	starting_threads(t_program *program)
{
	t_philo	*current;

	current = program->philo;
	while (current)
	{
		if (pthread_create(&current->thread, NULL, run_it, current) != 0)
			return (free_all(program), ft_putstr_fd("Failed to create thread\n",
					STDERR_FILENO), -1);
		current = current->next;
	}
	set_size_t(&program->start_mutex, &program->start_time, get_time());
	set_int(&program->start_mutex, &program->start, 1);
	return (0);
}

static void	joining_threads(t_program *program, pthread_t keeper_thread)
{
	t_philo	*current;

	current = program->philo;
	while (current)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	pthread_join(keeper_thread, NULL);
}

int	check_data(char *arg, int i)
{
	if ((i == 5) && (ft_atoll(arg) < 0 || ft_atoll(arg) > 2147483647))
		return (-1);
	else if (i != 5 && (ft_atoll(arg) <= 0 || ft_atoll(arg) > 2147483647))
		return (-1);
	return (0);
}

static int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '-')
				return (ft_putstr_fd("these aren't numbers, i know that\n",
						STDERR_FILENO), -1);
			if (check_data(argv[i], i) < 0)
				return (ft_putstr_fd("these arguments are so bad lol\n",
						STDERR_FILENO), -1);
			if (argv[5] && ft_atoll(argv[5]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	pthread_t	keeper_thread;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argv) < 0)
			return (-1);
		if (init_program(&program, argv, argc) < 0)
			return (free_all(&program), -1);
		if (init_philos(&program) < 0)
			return (free_all(&program), -1);
		if (starting_threads(&program) < 0)
			return (free_all(&program), -1);
		if (monitoring(&program, &keeper_thread) < 0)
			return (free_all(&program), -1);
		joining_threads(&program, keeper_thread);
		free_all(&program);
	}
	else
		ft_putstr_fd("ERROR\nWrong number of arguments !\n", STDERR_FILENO);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:54:08 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 11:32:45 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*last_philo(t_philo *lst)
{
	t_philo	*actuel;

	actuel = lst;
	if (actuel == NULL)
		return (actuel);
	while (actuel->next != NULL)
		actuel = actuel->next;
	return (actuel);
}

static void	append_philo_node(t_philo **lst, t_philo *new)
{
	t_philo	*actuel;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	actuel = last_philo(*lst);
	if (!actuel)
	{
		*lst = new;
		return ;
	}
	actuel->next = new;
	new->prev = actuel;
}

static void	init_philo_fork(t_philo *philo, t_program *program, int i)
{
	if (philo->nb_philo == 1)
	{
		philo->l_fork = &program->forks[i];
		philo->r_fork = NULL;
	}
	if (philo->name % 2 == 0)
	{
		philo->l_fork = &program->forks[i];
		philo->r_fork = &program->forks[(i + 1) % program->nb_philo];
	}
	else
	{
		philo->l_fork = &program->forks[(i + 1) % program->nb_philo];
		philo->r_fork = &program->forks[i];
	}
}

static int	create_philo_node(t_program *program, int i)
{
	t_philo	*new;

	new = NULL;
	new = malloc(sizeof(t_philo));
	if (!new)
		return (-1);
	memset(new, 0, sizeof(t_philo));
	new->name = i + 1;
	new->tt_die = program->tt_die;
	new->tt_eat = program->tt_eat;
	new->tt_sleep = program->tt_sleep;
	new->nb_philo = program->nb_philo;
	new->eating_goal = program->eating_goal;
	new->dead = &program->dead;
	new->start_time = &program->start_time;
	new->ate_last = get_time();
	init_philo_fork(new, program, i);
	new->start_mutex = &program->start_mutex;
	new->start = &program->start;
	new->write_lock = &program->write_lock;
	new->meal_lock = &program->meal_lock;
	new->dead_lock = &program->dead_lock;
	append_philo_node(&program->philo, new);
	return (0);
}

int	init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nb_philo)
	{
		if (create_philo_node(program, i) < 0)
			return (free_all(program), -1);
		i++;
	}
	return (0);
}

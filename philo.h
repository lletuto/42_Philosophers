/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:28 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/06/02 14:08:22 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				name;
	int				meals;
	size_t			ate_last;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	size_t			*start_time;
	int				nb_philo;
	int				eating_goal;
	int				*dead;
	int				*start;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*start_mutex;
	struct s_philo	*next;
	struct s_philo	*prev;

}					t_philo;

typedef struct s_program
{
	int				nb_philo;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	int				start;
	int				eating_goal;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	start_mutex;
	size_t			start_time;
	pthread_mutex_t	*forks;
	int				dead;
	t_philo			*philo;

}					t_program;

/*Monitoring*/
int					monitoring(t_program *program, pthread_t *keeper_thread);
int					is_fed(t_philo *philo);

/*Utils*/
void				ft_putstr_fd(char *s, int fd);
void				ft_usleep(size_t milliseconds, t_philo *philo);
size_t				get_time(void);
long long			ft_atoll(const char *str);
void				print_message(char *str, t_philo *philo);
void				set_size_t(pthread_mutex_t *mutex, size_t *dest,
						size_t value);
size_t				get_size_t(pthread_mutex_t *mutex, size_t *dest);
int					get_int(pthread_mutex_t *mutex, int *dest);
void				set_int(pthread_mutex_t *mutex, int *dest, int value);

/*Exec*/
int					did_you_just_die(t_philo *philo);
void				*run_it(void *args);

/*Init*/
int					init_philos(t_program *program);
int					init_program(t_program *program, char **argv, int argc);

/*Free*/
void				free_all(t_program *program);

#endif
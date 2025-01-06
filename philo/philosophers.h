/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:07 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/18 15:57:09 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_counter;
	long long		last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	long long		start_time;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				end;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	end_mutex;
}	t_table;

// utils.c
void		return_error(char *s);
long long	get_time_in_ms(void);
void		print_log(char *s, t_philo *philo);
int			is_end(t_table *table);

// parse.c
int			ft_atoi(char *s);
int			input_is_valid(int ac, char **av);

// init.c
void		init_table(t_table *table, int ac, char **av);

// simulation.c
void		start_simulation(t_table *table);

// supervisor.c
void		*supervisor_routine(void *arg);

#endif
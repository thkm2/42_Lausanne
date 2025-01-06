/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:33:12 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/18 16:19:59 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	if (philo->left_fork->id)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (is_end(philo->table))
			return (pthread_mutex_unlock(&philo->left_fork->mutex), 0);
		print_log("has taken a fork", philo);
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (is_end(philo->table))
			return (pthread_mutex_unlock(&philo->left_fork->mutex),
				pthread_mutex_unlock(&philo->right_fork->mutex), 0);
		print_log("has taken a fork", philo);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	if (philo->table->nb_philos == 1)
	{
		print_log("has taken a fork", philo);
		while (!is_end(philo->table))
			usleep(1000);
		return ;
	}
	if (!take_forks(philo))
		return ;
	print_log("is eating", philo);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->meal_counter += 1;
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->table->meal_mutex);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(900);
	while (!is_end(philo->table))
	{
		eat(philo);
		if (is_end(philo->table))
			return (NULL);
		print_log("is sleeping", philo);
		usleep(philo->table->time_to_sleep * 1000);
		if (is_end(philo->table))
			return (NULL);
		print_log("is thinking", philo);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	pthread_create(&supervisor, NULL, supervisor_routine, table);
	while (i < table->nb_philos)
	{
		pthread_create(&table->philos[i].thread, NULL,
			philo_routine, &table->philos[i]);
		i++;
	}
	pthread_join(supervisor, NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

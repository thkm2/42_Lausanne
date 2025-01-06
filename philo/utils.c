/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:23 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/18 15:56:48 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	return_error(char *s)
{
	printf("%s\n", s);
	exit(1);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void	print_log(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->log_mutex);
	printf("%lld %d ", get_time_in_ms() - philo->table->start_time, philo->id);
	printf("%s\n", s);
	pthread_mutex_unlock(&philo->table->log_mutex);
}

int	is_end(t_table *table)
{
	int	rs;

	rs = 0;
	pthread_mutex_lock(&table->end_mutex);
	if (table->end)
		rs = 1;
	pthread_mutex_unlock(&table->end_mutex);
	return (rs);
}

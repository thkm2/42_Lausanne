/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:29:19 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/13 14:01:35 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_free(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	free(table->forks);
	free(table->philos);
	table->forks = NULL;
	table->philos = NULL;
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->end_mutex);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	if (!input_is_valid(ac, av))
		return_error("bad arguments");
	init_table(&table, ac, av);
	start_simulation(&table);
	destroy_free(&table);
	return (0);
}

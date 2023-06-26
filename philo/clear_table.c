/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:27:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/26 22:18:18 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_forks(t_seat *seats, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
		pthread_mutex_destroy(&seats[i].fork);
}

int	clear_table(t_table *table)
{
	unsigned int		i;
	int		*result; //

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->seats[i].philo, (void **)&result) != 0)
			return (3);
		// printf("philo %d returned %d\n", table->seats[i].nr, *result);
		// write(1, "s\n", 2);
		i++;
	}
	pthread_mutex_destroy(&table->lazy_susan->start_mutex);
	pthread_mutex_destroy(&table->lazy_susan->printer_mutex);
	pthread_mutex_destroy(&table->lazy_susan->reaper_mutex);
	clear_forks(table->seats, table->philo_count);
	free(table->seats);
	free(table);
	return (0);
}
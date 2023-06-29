/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:27:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:09:24 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	clear_forks(t_seat *seats, unsigned int philo_count)
{
	unsigned int	i;

	i = 0;
	while (++i < philo_count)
	{
		pthread_mutex_destroy(&seats[i].fork);
		i++;
	}
}

int	escort_philos(t_table *table)
{
	unsigned int		i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->seats[i].philo, NULL) != 0)
		{
			while (i < table->philo_count)
			{
				pthread_detach(table->seats[i].philo);
				i--;
			}
			write(STDERR_FILENO, "pthread_join fail\n", 19);
			return (3);
		}
		i++;
	}
	return (0);
}

void	clear_table(t_table *table)
{
	pthread_mutex_destroy(&table->lazy_susan->start_mutex);
	pthread_mutex_destroy(&table->lazy_susan->printer_mutex);
	pthread_mutex_destroy(&table->lazy_susan->reaper_mutex);
	clear_forks(table->seats, table->philo_count);
	free(table->seats);
	free(table);
	return ;
}

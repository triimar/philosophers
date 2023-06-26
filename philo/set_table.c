/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:39:56 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/26 22:18:07 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	place_forks(t_seat *seats, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
		pthread_mutex_init(&seats[i].fork, NULL);
	return ;
}

int	set_table(t_table *table)
{
	unsigned int	i;

	i = -1;

	table->seats = malloc((table->philo_count) * sizeof(t_seat));
	if (!table->seats)
		return(EXIT_FAILURE); //free table
	table->lazy_susan->no_spagetti = 1;
	table->lazy_susan->death = 0;
	pthread_mutex_init(&table->lazy_susan->printer_mutex, NULL);
	pthread_mutex_init(&table->lazy_susan->start_mutex, NULL);
	pthread_mutex_init(&table->lazy_susan->reaper_mutex, NULL);
	
	while (++i < table->philo_count)
	{
		table->seats[i].nr = i + 1;
		table->seats[i].schedule = table->schedule;
		table->seats[i].lazy_susan = table->lazy_susan;
		if (i + 1 == table->philo_count)
			table->seats[i].next_fork = &table->seats[0].fork;
		else
			table->seats[i].next_fork = &table->seats[i + 1].fork;
	}
	place_forks(table->seats, table->philo_count);
	return (0);
}

int	seat_diners(t_seat *seats, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_create(&seats[i].philo, NULL, &routine, &seats[i]) != 0)
			return (1); //free shit
	}
	pthread_mutex_lock(&seats[0].lazy_susan->start_mutex);
	seats[0].lazy_susan->start_time = current_time();
	seats[0].lazy_susan->no_spagetti = 0;
	pthread_mutex_unlock(&seats[0].lazy_susan->start_mutex);
	return (0);
}
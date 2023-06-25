/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:39:56 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/25 23:18:37 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_seat			*current_seat;
	unsigned long	big_bang;
	unsigned long	prev_start;

	current_seat = (t_seat *)arg;
	
	while (1)
	{
		pthread_mutex_lock(&current_seat->lazy_susan->time_start);
		if (current_seat->lazy_susan->no_spagetti)
		{
			pthread_mutex_unlock(&current_seat->lazy_susan->time_start);
			usleep(1000);
		}
		else
		{
			big_bang = current_seat->lazy_susan->start_time;
			pthread_mutex_unlock(&current_seat->lazy_susan->time_start);
			break ;
		}
	}
	// while (current_time() < big_bang + 200)
	// 	usleep(1000);
	// big_bang = big_bang + 200;
	// current_seat->prev_start = current_time();
	prev_start = current_time();
	printer(&current_seat->lazy_susan->printer, \
		(prev_start - big_bang), current_seat->nr, " is starting");
	return ((void *) &current_seat->nr);
}

int	set_table(t_table *table)
{
	unsigned int	i;

	i = 0;

	table->seats = malloc((table->philo_count) * sizeof(t_seat));
	if (!table->seats)
		return(EXIT_FAILURE); //free table
	table->lazy_susan->no_spagetti = 1;
	pthread_mutex_init(&table->lazy_susan->printer, NULL);
	pthread_mutex_init(&table->lazy_susan->time_start, NULL);
	while (i < table->philo_count)
	{
		table->seats[i].nr = i + 1;
		table->seats[i].schedule = table->schedule;
		table->seats[i].lazy_susan = table->lazy_susan;
		table->seats[i].prev_start = table->lazy_susan->start_time;
		if (pthread_create(&table->seats[i].philo, NULL, \
		&routine, &table->seats[i]) != 0)
			return (1);
		if (i + 1 == table->philo_count)
			table->seats[i].next_fork = &table->seats[0].fork;
		else
		{
			table->seats[i].next_fork = &table->seats[i + 1].fork;
			pthread_mutex_lock(&table->lazy_susan->time_start);
			table->lazy_susan->no_spagetti = 0;
			table->lazy_susan->start_time = current_time();
			pthread_mutex_unlock(&table->lazy_susan->time_start);
		}		
		i++;
	}
	return (0);
}

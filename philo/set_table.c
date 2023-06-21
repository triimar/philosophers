/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:39:56 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/21 21:26:05 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*roll_dice(void *arg)
{
	// while (current_time() != current_seat->lazy_susan->start_time + 300)
	// 	usleep(1);
	t_seat *current_seat = (t_seat *)arg;

	while (current_seat->lazy_susan->no_pasta)
		usleep(1);
	current_seat->prev_start = current_time();
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	// while (current_time() != current_seat->prev_start + 100)
	printf("At time %ld this is philosopher nr %d\n", current_time(), current_seat->nr);
	// write(1, "o\n", 2);
	*result = value;
	return ((void *) result);
}

int	set_table(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->lazy_susan.no_pasta = 1;
	table->seats = malloc((table->philo_count) * sizeof(t_seat));
	if (!table->seats)
		return(EXIT_FAILURE); //free table
	// table->seats[table->philo_count] = '\0';
	while (i < table->philo_count)
	{
		table->seats[i].nr = i + 1;
		table->seats[i].schedule = table->schedule;
		table->seats[i].lazy_susan = &table->lazy_susan;
		table->seats[i].prev_start = table->lazy_susan.start_time;
		if (i + 1 == table->philo_count)
			table->seats[i].next_fork = &table->seats[0].fork;
		else
		{
			table->seats[i].next_fork = &table->seats[i + 1].fork;
			// table->lazy_susan.start_time = current_time();
		}
		if (pthread_create(&table->seats[i].philo, NULL, &roll_dice, &table->seats[i]) != 0)
			return (1);
		i++;
	}
	table->lazy_susan.no_pasta = 0;
	return (0);
}


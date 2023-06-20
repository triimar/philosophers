/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:39:56 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/20 21:47:13 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*roll_dice(void *arg)
{
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	t_seat *current_seat = (t_seat *)arg;
	sleep(2);
	printf("This is philosopher nr %d\n", current_seat->nr);
	*result = value;
	return ((void *) result);
}

int	set_table(t_table *table)
{
	int	i;

	i = 0;
	table->seats = malloc((table->philo_count) * sizeof(t_seat));
	if (!table->seats)
		return(EXIT_FAILURE); //free table
	// table->seats[table->philo_count] = '\0';
	while (i < table->philo_count)
	{
		table->seats[i].nr = i + 1;
		if (i + 1 == table->philo_count)
			table->seats[i].next_fork = &table->seats[0].fork;
		else
			table->seats[i].next_fork = &table->seats[i + 1].fork;
		table->seats[i].schedule = table->schedule;
		table->seats[i].lazy_susan = &table->lazy_susan;
		if (pthread_create(&table->seats[i].philo, NULL, &roll_dice, &table->seats[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}


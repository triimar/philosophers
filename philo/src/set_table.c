/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:39:56 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:10:01 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	place_forks(t_seat *seats, unsigned int philo_count)
{
	unsigned int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&seats[i].fork, NULL);
		i++;
	}
	return ;
}

static void	arrange_center(t_center *lazy_susan)
{
	lazy_susan->no_spagetti = 1;
	lazy_susan->death = 0;
	lazy_susan->start_time = 0;
	pthread_mutex_init(&lazy_susan->printer_mutex, NULL);
	pthread_mutex_init(&lazy_susan->start_mutex, NULL);
	pthread_mutex_init(&lazy_susan->reaper_mutex, NULL);
}

int	set_table(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->seats = malloc((table->philo_count) * sizeof(t_seat));
	if (!table->seats)
	{
		write(STDERR_FILENO, "malloc fail\n", 13);
		return (1);
	}
	arrange_center(table->lazy_susan);
	while (i < table->philo_count)
	{
		table->seats[i].nr = i + 1;
		table->seats[i].input = table->input;
		table->seats[i].lazy_susan = table->lazy_susan;
		if (i + 1 == table->philo_count)
			table->seats[i].next_fork = &table->seats[0].fork;
		else
			table->seats[i].next_fork = &table->seats[i + 1].fork;
		i++;
	}
	place_forks(table->seats, table->philo_count);
	return (0);
}

static void	set_timer(t_center *lazy_susan)
{
	pthread_mutex_lock(&lazy_susan->start_mutex);
	lazy_susan->start_time = current_time();
	lazy_susan->no_spagetti = 0;
	pthread_mutex_unlock(&lazy_susan->start_mutex);
}

int	seat_diners(t_seat *seats, unsigned int philo_count)
{
	unsigned int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_create(&seats[i].philo, NULL, &routine, &seats[i]) != 0)
		{
			while (--i > 0)
				pthread_detach(seats[i].philo);
			pthread_detach(seats[0].philo);
			write(STDERR_FILENO, "pthread_create fail\n", 21);
			return (2);
		}
		i++;
	}
	set_timer(seats[0].lazy_susan);
	return (0);
}

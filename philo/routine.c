/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:16:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/28 00:40:40 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_spagetti(t_ms *start_t, t_seat *current_seat)
{
	while (1)
	{
		pthread_mutex_lock(&current_seat->lazy_susan->start_mutex);
		if (current_seat->lazy_susan->no_spagetti)
		{
			pthread_mutex_unlock(&current_seat->lazy_susan->start_mutex);
			usleep(1000);
		}
		else
		{
			*start_t = current_seat->lazy_susan->start_time;
			pthread_mutex_unlock(&current_seat->lazy_susan->start_mutex);
			break ;
		}	
	}
	return ;
}

int	check_pulse(t_center *lazy_susan)
{
	pthread_mutex_lock(&lazy_susan->reaper_mutex);
	if (lazy_susan->death)
	{
		pthread_mutex_unlock(&lazy_susan->reaper_mutex);
		return (0);
	}
	pthread_mutex_unlock(&lazy_susan->reaper_mutex);
	return (1);
}

static void	philo_died(t_seat *seat, t_ms big_bang)
{
	if (check_pulse(seat->lazy_susan) == 0)
		return ;
	pthread_mutex_lock(&seat->lazy_susan->reaper_mutex);
	seat->lazy_susan->death = 1;
	pthread_mutex_unlock(&seat->lazy_susan->reaper_mutex);
	pthread_mutex_lock(&seat->lazy_susan->printer_mutex);
	printf("%-5ld %2d %s\n", (current_time() - big_bang), seat->nr, "died");
	pthread_mutex_unlock(&seat->lazy_susan->printer_mutex);
	return ;
}

void	*routine(void *arg)
{
	t_seat			*current_seat;
	t_ms			big_bang;
	t_philo			philo;

	big_bang = 0;
	current_seat = (t_seat *)arg;
	wait_spagetti(&big_bang, current_seat);
	philo.hunger_start = big_bang;
	philo.meal_count = 0;
	while (time_elapsed(philo.hunger_start) < current_seat->schedule->death_t)
	{
		if (check_pulse(current_seat->lazy_susan) == 0)
			return (NULL);
		if (eating(current_seat, big_bang, &philo.hunger_start) != 0)
			break ;
		if ((current_seat->schedule->must_eat != 0 && \
		++philo.meal_count == current_seat->schedule->must_eat) || \
		check_pulse(current_seat->lazy_susan) == 0)
			return (NULL);
		if (sleeping(current_seat, big_bang, philo.hunger_start) != 0)
			break ;
		printer(current_seat, big_bang, "is thinking");
	}
	philo_died(current_seat, big_bang);
	return (NULL);
}

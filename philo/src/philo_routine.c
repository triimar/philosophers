/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:16:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 23:51:34 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	wait_spagetti(t_ms *big_bang, t_seat *cur_seat)
{
	while (1)
	{
		pthread_mutex_lock(&cur_seat->lazy_susan->start_mutex);
		if (cur_seat->lazy_susan->no_spagetti)
		{
			pthread_mutex_unlock(&cur_seat->lazy_susan->start_mutex);
			usleep(500);
		}
		else
		{
			*big_bang = cur_seat->lazy_susan->start_time;
			pthread_mutex_unlock(&cur_seat->lazy_susan->start_mutex);
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
	t_seat			*cur_seat;
	t_philo			philo;
	t_ms			big_bang;

	cur_seat = (t_seat *)arg;
	big_bang = 0;
	wait_spagetti(&big_bang, cur_seat);
	philo.hunger_start = big_bang;
	philo.meals = 0;
	while (time_elapsed(philo.hunger_start) < cur_seat->input->death_t)
	{
		if (check_pulse(cur_seat->lazy_susan) == 0)
			return (NULL);
		if (eating(cur_seat, big_bang, &philo.hunger_start, philo.meals) != 0)
			break ;
		if (++philo.meals == cur_seat->input->must_eat || \
				check_pulse(cur_seat->lazy_susan) == 0)
			return (NULL);
		if (sleeping(cur_seat, big_bang, philo.hunger_start) != 0)
			break ;
		thinking(cur_seat, big_bang, philo.hunger_start);
	}
	philo_died(cur_seat, big_bang);
	return (NULL);
}

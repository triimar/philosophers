/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:16:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/27 00:41:55 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_spagetti(unsigned long *start_t, t_seat *current_seat)
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

void	eating(t_seat *seat, unsigned long big_bang, unsigned long *hunger_st)
{
	if (seat->nr % 2 != 0)
	{
		pthread_mutex_lock(&seat->fork);
		printer(seat, big_bang, "has taken a fork");
		if (&seat->fork == seat->next_fork)
		{
			usleep(1000 *(seat->schedule->death_t - time_elapsed(*hunger_st)));
			return ;
		}
		pthread_mutex_lock(seat->next_fork);
		printer(seat, big_bang, "has taken a fork");
		printer(seat, big_bang, "is eating");
		*hunger_st = current_time();
		usleep(1000 * seat->schedule->eat_t);
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
	}
	else
	{
		usleep(1000 * seat->schedule->eat_t);
		pthread_mutex_lock(seat->next_fork);
		printer(seat, big_bang, "has taken a fork");
		pthread_mutex_lock(&seat->fork);
		printer(seat, big_bang, "has taken a fork");
		printer(seat, big_bang, "is eating");
		*hunger_st = current_time();
		usleep(1000 * seat->schedule->eat_t);
		pthread_mutex_unlock(seat->next_fork);
		pthread_mutex_unlock(&seat->fork);
	}
}

int	sleeping(t_seat *seat, unsigned long big_bang, unsigned long hunger_start)
{
	unsigned long	i;

	i = 0;
	printer(seat, big_bang, "is sleeping");
	while (i < seat->schedule->sleep_t)
	{
		usleep(1000);
		if (time_elapsed(hunger_start) >= seat->schedule->death_t)
			return (1);
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_seat			*current_seat;
	unsigned long	big_bang;
	unsigned long	hunger_start;
	int				eats;

	eats = 0;
	current_seat = (t_seat *)arg;
	wait_spagetti(&big_bang, current_seat);
	hunger_start = big_bang;
	while (time_elapsed(hunger_start) < current_seat->schedule->death_t)
	{
		if (check_pulse(current_seat->lazy_susan) == 0)
			return ((void *) &current_seat->nr);
		eating(current_seat, big_bang, &hunger_start);
		eats++;
		if (current_seat->schedule->must_eat != 0 && eats == current_seat->schedule->must_eat)
			return ((void *) &current_seat->nr);			
		if (check_pulse(current_seat->lazy_susan) == 0)
			return ((void *) &current_seat->nr);
		if (sleeping(current_seat, big_bang, hunger_start) != 0)
			break ;
		if (check_pulse(current_seat->lazy_susan) == 0)
			return ((void *) &current_seat->nr);
		printer(current_seat, big_bang, "is thinking");
	}
	if (check_pulse(current_seat->lazy_susan) == 0)
		return ((void *) &current_seat->nr);
	pthread_mutex_lock(&current_seat->lazy_susan->reaper_mutex);
	current_seat->lazy_susan->death = 1;
	pthread_mutex_unlock(&current_seat->lazy_susan->reaper_mutex);
	printer(current_seat, big_bang, "died");
	pthread_mutex_unlock(&current_seat->lazy_susan->printer_mutex);
	return ((void *) &current_seat->nr);
}

	// current_seat->prev_start = current_time();
	// prev_start = current_time();
	// printer(&current_seat->lazy_susan->printer_mutex, \
	// 	big_bang, current_seat->nr, "is starting");
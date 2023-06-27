/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:50:57 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/27 23:14:00 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lonely_death(t_seat *seat, t_ms bang)
{
	usleep(1000 *(seat->schedule->death_t - time_elapsed(bang)));
	pthread_mutex_unlock(&seat->fork);
	return (1);
}

static int	eat_odd(t_seat *seat, t_ms bang, t_ms *hunger)
{
	pthread_mutex_lock(&seat->fork);
	if (time_elapsed(*hunger) >= seat->schedule->death_t)
	{
		pthread_mutex_unlock(&seat->fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	if (&seat->fork == seat->next_fork)
		return (lonely_death(seat, bang));
	pthread_mutex_lock(seat->next_fork);
	if (time_elapsed(*hunger) >= seat->schedule->death_t)
	{
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	printer(seat, bang, "is eating");
	*hunger = current_time();
	usleep(1000 * seat->schedule->eat_t);
	pthread_mutex_unlock(&seat->fork);
	pthread_mutex_unlock(seat->next_fork);
	return (0);
}

static int	eat_even(t_seat *seat, t_ms bang, t_ms *hunger)
{
	usleep(1000 * seat->schedule->eat_t);
	pthread_mutex_lock(seat->next_fork);
	if (time_elapsed(*hunger) >= seat->schedule->death_t)
	{
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	pthread_mutex_lock(&seat->fork);
	if (time_elapsed(*hunger) >= seat->schedule->death_t)
	{
		pthread_mutex_unlock(seat->next_fork);
		pthread_mutex_unlock(&seat->fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	printer(seat, bang, "is eating");
	*hunger = current_time();
	usleep(1000 * seat->schedule->eat_t);
	pthread_mutex_unlock(seat->next_fork);
	pthread_mutex_unlock(&seat->fork);
	return (0);
}

int	eating(t_seat *seat, t_ms big_bang, t_ms *hunger)
{
	if (seat->nr % 2 != 0)
		return (eat_odd(seat, big_bang, hunger));
	else
		return (eat_even(seat, big_bang, hunger));
}

int	sleeping(t_seat *seat, t_ms big_bang, t_ms hunger)
{
	t_ms	start;
	int		i;

	start = current_time();
	i = 0;
	if (time_elapsed(hunger) < seat->schedule->death_t)
		printer(seat, big_bang, "is sleeping");
	while (time_elapsed(start) < seat->schedule->sleep_t)
	{
		if (time_elapsed(hunger) >= seat->schedule->death_t)
			return (1);
		usleep(1000);
		i++;
	}
	return (0);
}

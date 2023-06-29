/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:50:57 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:09:31 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	lonely_death(t_seat *seat, t_ms bang)
{
	while (seat->input->death_t > time_elapsed(bang))
		usleep(1000);
	pthread_mutex_unlock(&seat->fork);
	return (1);
}

static int	eat_odd(t_seat *seat, t_ms bang, t_ms *hunger)
{
	pthread_mutex_lock(&seat->fork);
	printer(seat, bang, "has taken a fork");
	if (&seat->fork == seat->next_fork)
		return (lonely_death(seat, bang));
	pthread_mutex_lock(seat->next_fork);
	if (time_elapsed(*hunger) >= seat->input->death_t)
	{
		pthread_mutex_unlock(seat->next_fork);
		pthread_mutex_unlock(&seat->fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	printer(seat, bang, "is eating");
	*hunger = current_time();
	if (sleep_or_dead(*hunger, seat->input->eat_t, \
			seat->input->death_t) != 0)
	{
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	pthread_mutex_unlock(seat->next_fork);
	pthread_mutex_unlock(&seat->fork);
	return (0);
}

static int	eat_even(t_seat *seat, t_ms bang, t_ms *hunger)
{
	pthread_mutex_lock(seat->next_fork);
	printer(seat, bang, "has taken a fork");
	if (&seat->fork == seat->next_fork)
		return (lonely_death(seat, bang));
	pthread_mutex_lock(&seat->fork);
	if (time_elapsed(*hunger) > seat->input->death_t)
	{
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	printer(seat, bang, "is eating");
	*hunger = current_time();
	if (sleep_or_dead(*hunger, seat->input->eat_t, \
			seat->input->death_t) != 0)
	{
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	pthread_mutex_unlock(&seat->fork);
	pthread_mutex_unlock(seat->next_fork);
	return (0);
}

int	eating(t_seat *seat, t_ms big_bang, t_ms *hunger, int meals)
{
	if (seat->nr % 2 != 0)
	{
		if (meals == 0 && &seat->fork != seat->next_fork)
			usleep(1000 * seat->input->eat_t * 2 / 3);
		return (eat_odd(seat, big_bang, hunger));
	}
	else
		return (eat_even(seat, big_bang, hunger));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:50:57 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 01:27:39 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	lonely_death(t_seat *seat, t_ms bang)
{
	while (seat->schedule->death_t > time_elapsed(bang))
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
	if (time_elapsed(*hunger) >= seat->schedule->death_t)
	{
		pthread_mutex_unlock(seat->next_fork);
		pthread_mutex_unlock(&seat->fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	printer(seat, bang, "is eating");
	*hunger = current_time();
	if (sleeping_or_dead(*hunger, seat->schedule->eat_t, \
			seat->schedule->death_t) != 0)
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
	if (time_elapsed(*hunger) > seat->schedule->death_t)
	{
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	printer(seat, bang, "has taken a fork");
	printer(seat, bang, "is eating");
	*hunger = current_time();
	if (sleeping_or_dead(*hunger, seat->schedule->eat_t, \
			seat->schedule->death_t) != 0)
	{
		pthread_mutex_unlock(&seat->fork);
		pthread_mutex_unlock(seat->next_fork);
		return (1);
	}
	pthread_mutex_unlock(&seat->fork);
	pthread_mutex_unlock(seat->next_fork);
	return (0);
}

int	eating(t_seat *seat, t_ms big_bang, t_ms *hunger, int meal_count)
{
	if (seat->nr % 2 != 0)
	{
		if (meal_count == 0 && &seat->fork != seat->next_fork)
			usleep(1000 * seat->schedule->eat_t * 3 / 4);
		return (eat_odd(seat, big_bang, hunger));
	}
	else
		return (eat_even(seat, big_bang, hunger));
}

void	thinking(t_seat *seat, t_ms big_bang, t_ms hunger_start)
{
	t_ms	think_t;
	t_ms	think_start;	

	think_start = current_time();
	printer(seat, big_bang, "is thinking");
	if (seat->schedule->death_t <= time_elapsed(hunger_start))
		return ;
	else
	{
		think_t = (seat->schedule->death_t - time_elapsed(hunger_start)) * 2 / 3;
		while (think_t >= time_elapsed(think_start))
			usleep(500);
	}
	return ;
}

// int	sleeping(t_seat *seat, t_ms big_bang, t_ms hunger)
// {
// 	printer(seat, big_bang, "is sleeping");
// 	if (sleeping_or_dead(hunger, seat->schedule->sleep_t, seat->schedule->death_t) != 0)
// 		return (1);
// 	return (0);
// }

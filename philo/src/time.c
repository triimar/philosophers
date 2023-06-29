/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:00:48 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:08:51 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_ms	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms)time.tv_sec * 1000 + (t_ms)time.tv_usec / 1000);
}

t_ms	time_elapsed(t_ms start)
{
	return (current_time() - start);
}

int	sleep_or_dead(t_ms hunger_start, t_ms sleep_time, t_ms death_time)
{
	t_ms	start_time;

	start_time = current_time();
	while (time_elapsed(start_time) <= sleep_time)
	{
		if (time_elapsed(hunger_start) >= death_time)
			return (1);
		usleep(100);
	}
	return (0);
}

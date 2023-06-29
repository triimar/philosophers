/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:37:06 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:20:45 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleeping(t_seat *seat, t_ms big_bang, t_ms hunger)
{
	printer(seat, big_bang, "is sleeping");
	if (sleep_or_dead(hunger, seat->input->sleep_t, seat->input->death_t) != 0)
		return (1);
	return (0);
}

void	thinking(t_seat *seat, t_ms big_bang, t_ms hunger_start)
{
	t_ms	think_t;
	t_ms	think_start;	

	think_start = current_time();
	printer(seat, big_bang, "is thinking");
	if (seat->input->death_t <= time_elapsed(hunger_start))
		return ;
	else
	{
		think_t = (seat->input->death_t - \
				time_elapsed(hunger_start)) * 2 / 3;
		while (think_t > time_elapsed(think_start))
			usleep(100);
	}
	return ;
}

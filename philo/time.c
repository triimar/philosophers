/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:00:48 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/27 19:41:35 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ms	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms) time.tv_sec * 1000 + \
	(t_ms) time.tv_usec / 1000);
}

t_ms	time_elapsed(t_ms start)
{
	return (current_time() - start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:00:48 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/21 14:51:53 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long) time.tv_sec * 1000 + \
	(unsigned long)time.tv_usec / 1000);
}

unsigned long	time_elapsed(unsigned long start)
{
	return (current_time() - start);
}

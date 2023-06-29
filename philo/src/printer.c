/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:14:44 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:09:56 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printer(t_seat	*seat, t_ms big_bang, char *str)
{
	pthread_mutex_lock(&seat->lazy_susan->printer_mutex);
	if (check_pulse(seat->lazy_susan) == 0)
	{
		pthread_mutex_unlock(&seat->lazy_susan->printer_mutex);
		return ;
	}
	printf("%-5ld %2d %s\n", (current_time() - big_bang), seat->nr, str);
	pthread_mutex_unlock(&seat->lazy_susan->printer_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:14:44 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/27 00:36:34 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	ft_putnbr_unsigned(unsigned long n, int fd)
// {
// 	char	digit;

// 	if (n >= 10)
// 	{
// 		ft_putnbr_unsigned((n / 10), fd);
// 		digit = (n % 10) + '0';
// 		write(fd, &digit, 1);
// 	}
// 	else
// 	{
// 		digit = n + '0';
// 		write (fd, &digit, 1);
// 	}
// 	return ;	
// }


void	printer(t_seat	*seat, unsigned long big_bang, char *str)
{
	if (check_pulse(seat->lazy_susan) == 0)
	{
		pthread_mutex_lock(&seat->lazy_susan->printer_mutex);
		printf("%3ld %2d %s\n", (current_time() - big_bang), seat->nr, str);
		return ;
	}
	pthread_mutex_lock(&seat->lazy_susan->printer_mutex);
	printf("%3ld %2d %s\n", (current_time() - big_bang), seat->nr, str);
	pthread_mutex_unlock(&seat->lazy_susan->printer_mutex);
}

// void	printer(pthread_mutex_t *mutex, unsigned long t, int n, char *str)
// {
// 	pthread_mutex_lock(mutex);
// 	printf("%3ld %2d %s\n", current_time() - t, n, str);
// 	pthread_mutex_unlock(mutex);
// }
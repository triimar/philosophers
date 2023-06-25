/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:14:44 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/25 23:24:17 by tmarts           ###   ########.fr       */
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


void	printer(pthread_mutex_t *mx, unsigned long t, int n, char *str)
{
	pthread_mutex_lock(mx);
	// ft_putnbr_unsigned(t, 1);
	// write(1, "\n", 1);
	// str = NULL;
	// n = 1;
	printf("%03ld %d %s\n", t, n, str);
	pthread_mutex_unlock(mx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:27:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/25 22:59:18 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_table(t_table *table)
{
	unsigned int		i;
	int		*result; //

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->seats[i].philo, (void **)&result) != 0)
			return (3);
		printf("philo %d returned %d\n", table->seats[i].nr, *result);
		// write(1, "s\n", 2);
		i++;
	}
	pthread_mutex_destroy(&table->lazy_susan->time_start);
	pthread_mutex_destroy(&table->lazy_susan->printer);
	free(table->seats);
	free(table);
	return (0);
}
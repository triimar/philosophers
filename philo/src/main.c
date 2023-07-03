/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:25:53 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/30 15:26:58 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*	argv[1] - number_of_philosophers
	argv[2] - time_to_die
	argv[3] - time_to_eat
	argv[4] - time_to_sleep
	argv[5] - number_of_times_each_philosopher_must_eat (optional)	*/

int	main(int argc, char **argv)
{
	t_table			*table;
	t_input			s_input;
	t_center		lazy_susan;

	if (basic_input_check(argc, argv + 1) != 0)
		return (EXIT_FAILURE);
	table = malloc(sizeof(t_table));
	if (!table)
	{
		write(STDERR_FILENO, "malloc fail\n", 13);
		return (EXIT_FAILURE);
	}
	if (init_input((argv + 1), &s_input, &table->philo_count) != 0)
		return (free(table), EXIT_FAILURE);
	table->input = &s_input;
	table->lazy_susan = &lazy_susan;
	if (set_table(table) != 0)
		return (free(table), EXIT_FAILURE);
	if (seat_diners(table->seats, table->philo_count) != 0)
		return (clear_table(table), EXIT_FAILURE);
	if (escort_philos(table) != 0)
		return (clear_table(table), EXIT_FAILURE);
	clear_table(table);
	return (EXIT_SUCCESS);
}

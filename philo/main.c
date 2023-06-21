/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:25:53 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/21 21:22:16 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
• Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.*/

#include "philo.h"

	//argv[1] - number_of_philosophers
	//argv[2] - time_to_die
	//argv[3] - time_to_eat
	//argv[4] - time_to_sleep
	//argv[5] - number_of_times_each_philosopher_must_eat (optional argument)


int	main(int argc, char **argv)
{
	t_table			*table;
	t_input			s_input;
	t_center		lazy_susan;

	if (basic_input_check(argc, argv + 1) != 0)
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (2);
	if (init_input((argv + 1), &s_input, &table->philo_count) != 0)
		return (1);
	printf("%u, %ld, %ld, %ld, %d\n", table->philo_count, s_input.death_t, s_input.eat_t, s_input.sleep_t, s_input.must_eat);
	table->schedule = &s_input;
	lazy_susan.start_time = current_time();
	table->lazy_susan = lazy_susan;
	printf("start time %ld\n", lazy_susan.start_time);
	set_table(table);
	clear_table(table);
	printf("current time %ld\n", current_time());
	return (0);
}

// t_milliseconds	time_now(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
	
// 	return ((t_milliseconds)time.tv_sec * 1000 + \
// 		(t_milliseconds)time.tv_usec / 1000);
// }
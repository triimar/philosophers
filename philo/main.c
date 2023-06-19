/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:25:53 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/19 21:38:26 by tmarts           ###   ########.fr       */
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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long		intvalue;
	int				neg_pos;

	intvalue = 0;
	neg_pos = 1;
	while ((*str == ' ' || *str == '\f' || *str == '\n'
			|| *str == '\r' || *str == '\t' || *str == '\v'))
		str++;
	if (*str == '-')
	{
		neg_pos = -1;
		str++;
	}	
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		intvalue = intvalue * 10 + (*str - '0');
		if (intvalue < 0 && neg_pos < 0)
			return (0);
		if (intvalue < 0 && neg_pos > 0)
			return (-1);
		str++;
	}
	return ((int)(intvalue * neg_pos));
}
// static int	ft_atoi_time_converter(const char *str, int *time)
// {
// 	int		intvalue;
// 	char	*chr;

// 	intvalue = 0;
// 	chr = (char *)str;
// 	while (chr && (*chr == ' ' || *chr == '\t'))
// 		chr++;
// 	while (*chr != '\0')
// 	{
// 		if (!(*chr >= '0' && *chr <= '9'))
// 			return (EXIT_FAILURE);
// 		if (intvalue <= (INT_MAX - (*chr - '0')) / 10)
// 		{
// 			intvalue = intvalue * 10 + (*chr - '0');
// 			chr++;
// 		}
// 		else
// 			return (EXIT_FAILURE);
// 	}
// 	*data = (int)intvalue;
// 	return (EXIT_SUCCESS);
// }

void *roll_dice(void *arg)
{
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	t_seat *current_seat = (t_seat *)arg;
	sleep(2);
 	printf("This is philosopher nr %d and I have %d fork\n", current_seat->nr, current_seat->fork);
	*result = value;
	return ((void *) result);
}

	//argv[1] - number_of_philosophers
	//argv[2] - time_to_die
	//argv[3] - time_to_eat
	//argv[4] - time_to_sleep
	//argv[5] - number_of_times_each_philosopher_must_eat (optional argument)
int	main(int argc, char **argv)
{
	t_input	s_input;
	t_seat	**table;
	int		philo_n;
	int		i;
	int		*result;

	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (basic_input_check(argv + 1) != 0)
		return (1);
	if (init_input_data((argv + 1), &s_input, &philo_n) != 0)
		return (1);
	printf("philos: %d, die: %d, eat: %d, sleep: %d, must: %d\n", \
	philo_n, s_input.death_t, s_input.eat_t, s_input.sleep_t, \
	s_input.must_eat);
	table = malloc((philo_n + 1) * sizeof(t_seat *));
	if (!table)
		return (2);
	table[philo_n] = NULL;
	while (i < philo_n)
	{
		table[i] = malloc(sizeof(t_seat));
		if (!table[i])
			return (2);
		table[i]->nr = i + 1;
		table[i]->fork = 1;
		if (pthread_create(&table[i]->philo, NULL, &roll_dice, table[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philo_n)
	{
		if (pthread_join(table[i]->philo, (void **)&result) != 0)
			return (3);
		printf("philo %d returned %d\n", table[i]->nr, *result);
		free(table[i]);
		free(result);
		i++;
	}
	free(table);
	return (0);
}


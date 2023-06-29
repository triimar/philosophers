/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:44:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/29 20:09:45 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	if (i > 10)
		return (0);
	return (1);
}

int	basic_input_check(int argc, char **args)
{
	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, "input error\n", 12);
		return (EXIT_FAILURE);
	}
	if (!ft_isdigit_str(args[0]) || !ft_isdigit_str(args[1]) || \
	!ft_isdigit_str(args[2]) || !ft_isdigit_str(args[3]))
	{
		write(STDERR_FILENO, "input error\n", 12);
		return (EXIT_FAILURE);
	}
	if (args[4] && !ft_isdigit_str(args[4]))
	{
		write(STDERR_FILENO, "input error\n", 12);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static unsigned long	ft_philo_atoi(const char *str)
{
	unsigned long long		intvalue;

	intvalue = 0;
	while (*str >= 48 && *str <= 57)
	{
		intvalue = intvalue * 10 + (*str - '0');
		str++;
	}
	return ((unsigned long)(intvalue));
}

int	init_input(char **args, t_input *s_input, unsigned int *philos)
{
	*philos = ft_philo_atoi(args[0]);
	s_input->death_t = (t_ms)ft_philo_atoi(args[1]);
	s_input->eat_t = (t_ms)ft_philo_atoi(args[2]);
	s_input->sleep_t = (t_ms)ft_philo_atoi(args[3]);
	if (args[4])
		s_input->must_eat = ft_philo_atoi(args[4]);
	else
		s_input->must_eat = 0;
	if (*philos <= 0 || s_input->death_t <= 0 || \
	s_input->eat_t <= 0 || s_input->sleep_t <= 0)
	{
		write(STDERR_FILENO, "input error\n", 12);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

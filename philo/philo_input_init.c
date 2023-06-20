/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:44:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/20 17:38:39 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	ft_atoi(const char *str)
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

int	init_input_data(char **args_to_atoi, t_input *s_input, int *philo_n)
{
	*philo_n = ft_atoi(args_to_atoi[0]);
	s_input->death_t = ft_atoi(args_to_atoi[1]);
	s_input->eat_t = ft_atoi(args_to_atoi[2]);
	s_input->sleep_t = ft_atoi(args_to_atoi[3]);
	if (args_to_atoi[4])
		s_input->must_eat = ft_atoi(args_to_atoi[4]);
	else
		s_input->must_eat = 0;
	if (*philo_n <= 0 || s_input->death_t <= 0 || \
	s_input->eat_t <= 0 || s_input->sleep_t <= 0 \
	|| s_input->must_eat < 0)
		return (EXIT_FAILURE); //
	return (EXIT_SUCCESS);	
}

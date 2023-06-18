/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:38:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/18 22:18:19 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //ft_printf
# include <string.h> //mamset
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday, settimeofday
# include <pthread.h> //pthread_create,
# include <limits.h>

typedef struct s_input
{
	int	death_t;
	int	eat_t;
	int	sleep_t;
	int	must_eat;
}	t_input;

typedef struct s_seat
{
	int					philo;
	pthread_t			philo_thread;
	// pthread_mutex_t		check_fork;
	// int					fork;
}	t_seat;

typedef struct s_table
{
	t_seat	*table;
	// t_input	schedule;
}	t_table;

int	basic_input_check(char **args);
int	init_input_data(char **args_to_atoi, t_input *s_input, int *philo_n);


#endif
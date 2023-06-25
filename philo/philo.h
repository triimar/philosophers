/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:38:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/25 23:07:40 by tmarts           ###   ########.fr       */
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
	unsigned long	death_t;
	unsigned long	eat_t;
	unsigned long	sleep_t;
	int				must_eat;
}	t_input;

typedef struct s_center
{
	pthread_mutex_t		printer;
	pthread_mutex_t		reaper;
	pthread_mutex_t		time_start;
	int					no_spagetti;
	unsigned long		start_time;
}	t_center;

typedef struct s_seat
{
	pthread_t			philo;
	unsigned int		nr;
	pthread_mutex_t		fork;
	pthread_mutex_t		*next_fork;
	t_input				*schedule;
	t_center			*lazy_susan;
	unsigned long		prev_start;
}	t_seat;

typedef struct s_table
{
	unsigned int		philo_count;
	t_seat				*seats;
	t_input				*schedule;
	pthread_t			waiter;
	t_center			*lazy_susan;
}	t_table;

int				basic_input_check(int argc, char **args);
int				init_input(char **args, t_input *s_input, unsigned int *philos);
int				set_table(t_table *table);
void			*routine(void *arg);
int				clear_table(t_table *table);
unsigned long	current_time(void);
unsigned long	time_elapsed(unsigned long start);
void			printer(pthread_mutex_t *mx, unsigned long t, int n, char *str);

#endif
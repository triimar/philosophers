/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:38:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/27 00:47:25 by tmarts           ###   ########.fr       */
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
	pthread_mutex_t		printer_mutex;
	pthread_mutex_t		reaper_mutex;
	pthread_mutex_t		start_mutex;
	int					no_spagetti;
	int					death;
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
}	t_seat;

typedef struct s_table
{
	unsigned int		philo_count;
	t_seat				*seats;
	t_input				*schedule;
	t_center			*lazy_susan;
}	t_table;

int				basic_input_check(int argc, char **args);
int				init_input(char **args, t_input *s_input, unsigned int *philos);
int				set_table(t_table *table);
int				seat_diners(t_seat *seats, int philo_count);
void			*routine(void *arg);
int				clear_table(t_table *table);
unsigned long	current_time(void);
unsigned long	time_elapsed(unsigned long start);
int				check_pulse(t_center *lazy_susan);
void			printer(t_seat	*seat, unsigned long big_bang, char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:38:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/30 15:27:24 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef unsigned long	t_ms;

typedef struct s_input
{
	t_ms			death_t;
	t_ms			eat_t;
	t_ms			sleep_t;
	unsigned int	must_eat;
	int				philo_c;
}	t_input;

typedef struct s_center
{
	pthread_mutex_t	printer_mutex;
	pthread_mutex_t	reaper_mutex;
	pthread_mutex_t	start_mutex;
	int				no_spagetti;
	int				death;
	t_ms			start_time;
}	t_center;

typedef struct s_seat
{
	pthread_t		philo;
	unsigned int	nr;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	t_input			*input;
	t_center		*lazy_susan;
}	t_seat;

typedef struct s_table
{
	unsigned int	philo_count;
	t_seat			*seats;
	t_input			*input;
	t_center		*lazy_susan;
}	t_table;

typedef struct s_philo
{
	t_ms			hunger_start;
	unsigned int	meals;
}	t_philo;

/*	philo_input_init.c	*/
int		basic_input_check(int argc, char **args);
int		init_input(char **args, t_input *s_input, unsigned int *philos);
/*	set_table.c	*/
int		set_table(t_table *table);
int		seat_diners(t_seat *seats, unsigned int philo_count);
/*	philo_routine.c	*/
void	*routine(void *arg);
int		check_pulse(t_center *lazy_susan);
/*	eat.c	*/
int		eating(t_seat *seat, t_ms big_bang, t_ms *hunger, int meals);
/*	sleep_and_think.c	*/
int		sleeping(t_seat *seat, t_ms big_bang, t_ms hunger);
void	thinking(t_seat *seat, t_ms big_bang, t_ms hunger_start);
/*	clear_table.c	*/
int		escort_philos(t_table *table);
void	clear_table(t_table *table);
/*	time.c	*/
t_ms	current_time(void);
t_ms	time_elapsed(t_ms start);
int		sleep_or_dead(t_ms hunger_start, t_ms sleep_time, t_ms death_time);
/*	printer.c	*/
void	printer(t_seat	*seat, t_ms big_bang, char *str);

#endif
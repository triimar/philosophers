# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 16:08:32 by tmarts            #+#    #+#              #
#    Updated: 2023/06/29 20:35:59 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo
CFLAGS 			:= -Wall -Wextra -Werror -pthread -g3 #-fsanitize=thread

INCLUDE_DIR		:= include
HEADERS 		:= -I $(INCLUDE_DIR)

SRCS	:= \
	src/main.c \
	src/philo_input_init.c \
	src/set_table.c \
	src/philo_routine.c \
	src/eat.c \
	src/sleep_and_think.c \
	src/time.c \
	src/printer.c \
	src/clear_table.c

OBJS := $(SRCS:.c=.o)

all : $(NAME)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
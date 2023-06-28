# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 16:08:32 by tmarts            #+#    #+#              #
#    Updated: 2023/06/28 22:50:25 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
GREEN	:= \033[32;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

#//= Mandatory part =//#
NAME			:= philo
CFLAGS 			:= -Wall -Wextra -Werror -pthread -g3 #-fsanitize=address
#CFLAGS 			+= -fsanitize=thread
INCLUDE_DIR		:= ./include

HEADERS 		:= -I $(INCLUDE_DIR)

SRCS	:= \
	src/main.c \
	src/philo_input_init.c \
	src/set_table.c \
	src/philo_routine.c \
	src/eat_sleep_think.c \
	src/time.c \
	src/printer.c \
	src/clear_table.c

OBJS := $(SRCS:.c=.o)

#//= Make Rules =//#
all : $(NAME)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) && \
	echo "$(WHITE)>> Mandatory part - Philosophers <<$(RESET)" && \
	echo "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
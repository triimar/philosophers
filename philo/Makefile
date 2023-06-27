# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 16:08:32 by tmarts            #+#    #+#              #
#    Updated: 2023/06/28 00:39:10 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

#//= Mandatory part =//#
NAME			:= philo
# CC			:= cc # ($(CC) is by default cc in makefile)
CFLAGS 			:= -Wall -Wextra -Werror -pthread -g3 #-fsanitize=address
#CFLAGS 			+= -fsanitize=thread
INCLUDE_DIR		:= ./include

HEADERS 		:= -I $(INCLUDE_DIR)

SRCS	:= \
	main.c \
	philo_input_init.c \
	set_table.c \
	routine.c \
	eat_sleep_think.c \
	time.c \
	printer.c \
	clear_table.c

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
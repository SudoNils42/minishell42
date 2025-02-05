# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 19:02:17 by nbonnet           #+#    #+#              #
#    Updated: 2025/02/05 19:10:01 by nbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PATH_LIBFT = ./libft
LIBFT = $(PATH_LIBFT)/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = builtins/pwd.c \
       builtins/env.c \
       builtins/echo.c \
       builtins/cd.c \
       builtins/cd2.c \
       builtins/export1.c \
       builtins/export2.c \
       builtins/unset.c \
       builtins/exit.c \
       n_main.c \
       n_utils.c \
       n_exec_utils.c \
       n_exec.c \
       n_command_path.c \
       n_init.c \
       n_exec_builtins.c \
       n_pipe_or_word.c \
       n_redirect.c \
	   make_env.c \
       parse.c \
       signals.c \
	   n_redirect_utils.c \
	   n_parsing.c \
	   free.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)

$(LIBFT):
	make -C $(PATH_LIBFT)

clean:
	rm -rf $(OBJS)
	make clean -C $(PATH_LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PATH_LIBFT)

norm :
	@norminette $(SRCS) minishell.h

re: fclean all

.PHONY: all clean fclean re norm

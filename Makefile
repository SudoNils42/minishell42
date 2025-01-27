# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 16:03:28 by nbonnet           #+#    #+#              #
#    Updated: 2025/01/22 19:13:37 by nbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PATH_LIBFT = ./libft
LIBFT = $(PATH_LIBFT)/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = n_main.c n_utils.c n_command.c n_command_path.c n_init.c n_pipe_or_word.c n_redirect.c n_token.c
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

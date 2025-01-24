/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:14:19 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/24 17:29:26 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_MINISHELL_H
# define N_MINISHELL_H
# include "./libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIRECT_IN 3
# define TOKEN_REDIRECT_OUT 4
# define TOKEN_EOF 5

typedef struct s_token
{
	char		*value;
	int			type;
	int			number;
}				t_token;

typedef struct s_command
{
	char		**args;
	int			args_count;
	int			input_fd;
	int			output_fd;
	int			fd_in;
	int			fd_out;
}				t_command;

typedef struct s_data
{
	char		**env;
	char		*input;
	int			token_count;
	int			current_token;
	int			total_pipes;
	pid_t		pid;
	pid_t		*pids;
	int			pid_index;
	t_command	*command;
	t_token		*tokens;
}				t_data;

void			start(t_data *data);
void			init_data(t_data *data, char **env);
t_token			*tokenize_input(t_data *data);
int				get_token_type(char *token);
int				parse_command(t_data *data);
int				process_command_line(t_data *data);
int				execute_command(t_data *data);
char			*find_command_path(char *cmd);
char			*ft_strjoin_with_slash(const char *s1, const char *s2);
int				ft_strcmp(char *s1, char *s2);
int				if_pipe(t_token token);
int				redirect_in(t_data *data, int token_count);
int				redirect_out(t_data *data, int token_count);
int				if_word(t_data *data);
void			parent_close_fd(t_data *data);

#endif

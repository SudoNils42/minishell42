/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:14:19 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/16 18:07:00 by nbonnet          ###   ########.fr       */
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

typedef struct s_data
{
	char	***cmd_arg_pipe;
	char	**av;
	char	**env;
	char	**bash_cmd;
	char	**cmd_arg;
	char	**dir;
	char	*input;
	char	*input_cpy;
	char	*path;
	char	*full_path;
	int		fd[2];
	int		cmd_arg_count;
	int		fd_input;
	int		ac;

	pid_t	pid;

}			t_data;

// main.c
int			main(int ac, char **av, char **env);

// utils.c
char		*ft_strjoin_with_slash(const char *s1, const char *s2);
void		ft_strcpy(char *dst, char *src);
int			ft_strcmp(const char *s1, const char *s2);

// init.c
void		init_data(t_data *data, int ac, char **av, char **env);

// bash.c
int			child_process(t_data *data);
void		parent_process(t_data *data);
void		start_bash(t_data *data);

// pipe.c
void		create_pipe(t_data *data);
void		split_cmd_arg_pipe(t_data *data);
void		start_pipe(t_data *data);
void		execute_cmd_arg(t_data *data, int index);

#endif

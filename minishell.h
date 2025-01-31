/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/31 16:44:00 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <linux/limits.h>

# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIRECT_IN 3
# define TOKEN_REDIRECT_OUT 4
# define TOKEN_REDIRECT_APPEND 5
# define TOKEN_EOF 6

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
	char		**exp;
	char		*input;
	int			token_count;
	int			current_token;
	int			total_pipes;
	int			prev_pipe_read_end;
	pid_t		pid;
	pid_t		*pids;
	int			pid_index;
	int			exit_status;
	t_command	*command;
	t_token		*tokens;
}				t_data;

// main.c
void			start(t_data *data);

// init.c
void			init_data(t_data *data, char **env);
void			init_command(t_data *data);
void			init_pid_list(t_data *data);

// token.c
t_token			*tokenize_input(t_data *data);
int				get_token_type(char *token);

// exec_utils.c
void			wait_for_children(t_data *data);
void			run_child_process(t_data *data, char *cmd_path, int is_builtin);
void			cleanup_parent(t_data *data);
void			setup_pipe(t_data *data, int pipe_fd[2]);
void			prepare_pipe_connection(t_data *data);
void			apply_redirections(t_data *data);
void			restore_redirections(t_data *data);

// exec.c
int				parse_command(t_data *data);
int				process_command_line(t_data *data);
int				execute_command(t_data *data);
void			handle_previous_pipe(t_data *data);

// command_path.c
char			*find_command_path(char *cmd, t_data *data);
char			*ft_strjoin_with_slash(const char *s1, const char *s2);
char			*find_path(t_data *data);

// utils.c
int				ft_strcmp(char *s1, char *s2);

// redirect.c
int				redirect_in(t_data *data, int token_count);
int				redirect_out(t_data *data, int token_count);
int				handle_redirection(t_data *data);

// pipe_or_word.c
int				if_word(t_data *data);
int				if_pipe(t_token token);

void			exec_builtins(t_data *data);
int				is_builtin(t_data *data);

// BUILTINS
//cd.c
int				ft_cd(t_data *data);
void			update_old_pwd_env(t_data *data);
void			update_old_pwd_env2(t_data *data, char *pwd);
void			update_old_pwd_exp(t_data *data);
void			update_old_pwd_exp2(t_data *data, char *pwd);
//cd2.c
int				ft_cd2(t_data *data);
void			update_pwd_env(t_data *data);
void			update_pwd_exp(t_data *data);
char			*ft_get_home(t_data *data);
//echo.c
int				ft_echo(t_data *data);
void			ft_echo_print(t_data *data, int i, int line);
//env.c
int				ft_env(t_data *data);
//exit.c
int				ft_exit(void);
//export.c
void			bubble_sort(char **env);
void			valid_var_name(t_data *data, int i);
int				is_valid_var_name(char *var);
void			export_without_args(t_data *data);
int				ft_export(t_data *data);
//export2.c
void			update_env_with_equal(t_data *data, char *str);
void			update_exp_with_equal(t_data *data, char *str);
void			update_exp_without_equal(t_data *data, char *str);

//pwd.c
int				ft_pwd(void);
//unset.c
int				ft_unset(t_data *data);
void			unset_var(t_data *data, char *var_name);
void			unset_var_in_exp(t_data *data, char *var_name);

//parse.c
int				check_args(char *str);
int				is_quotes_open(char *str);
void			check_dollars(t_data *data);
void			get_exit_status(t_data *data, int i);
char			*get_env_value(char *str, t_data *data);

//signals.c
void			signals(void);
void			sig_int(int signal);

//make_env.c
void			make_env(t_data *data, char **env);
void			make_exp(t_data *data, char **env);

#endif

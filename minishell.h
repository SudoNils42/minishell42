/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:18:44 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/20 17:35:52 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
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
# define TOKEN_REDIRECT_APPEND 5
# define TOKEN_HEREDOC 6
# define TOKEN_SQUOTE 7
# define TOKEN_DQUOTE 8
# define TOKEN_NO_QUOTE 9
# define ERROR "minishell: syntax error near unexpected token `newline'\n"

typedef struct s_sub_token
{
	char		*content;
	int			type;
}				t_sub_token;

typedef struct s_token
{
	char		*value;
	int			type;
	t_sub_token	**sub_tokens;
}				t_token;

typedef struct s_command
{
	char		**args;
	int			args_count;
	int			input_fd;
	int			output_fd;
	int			fd_in;
	int			fd_out;
	int			error_pipe_read;
	int			error_pipe_write;
}				t_command;

typedef struct s_data
{
	char		**env;
	char		**exp;
	char		**raw_tokens;
	char		*input;
	char		*content;
	int			token_count;
	int			start;
	int			flag_error;
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
void			init_data(t_data *data);
void			init_command(t_data *data);
void			init_pid_list(t_data *data);

// exec_utils.c
void			wait_for_children(t_data *data);
void			run_child_process(t_data *data, char *cmd_path,
					int is_builtin_cmd);
void			cleanup_parent(t_data *data);
void			setup_pipe(t_data *data, int pipe_fd[2]);
void			prepare_pipe_connection(t_data *data);
void close_all_fds(t_data *data);

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
char			*ft_strndup(const char *s, int n);
int				ft_isspace(char c);
// redirect.c
int				redirect_in(t_data *data, int token_count);
int				redirect_out(t_data *data, int token_count);
int				handle_redirection(t_data *data);

// redirect_utils.c
int				process_redirection(int processed, t_data *data);
void			inside_heredoc(char *delimiter, int pipe_fd[2]);
void			print_first_error(char *filename);
void			print_error(char *filename);

// exec_builtins.c
void			exec_builtins(t_data *data);
int				is_builtin(t_data *data);

// BUILTINS
// cd.c
int				ft_cd(t_data *data);
void			update_old_pwd_env(t_data *data);
void			update_old_pwd_env2(t_data *data, char *pwd);
void			update_old_pwd_exp(t_data *data);
void			update_old_pwd_exp2(t_data *data, char *pwd);
// cd2.c
void			ft_cd2(t_data *data);
int				ft_cd3(t_data *data);
void			update_pwd_env(t_data *data);
void			update_pwd_exp(t_data *data);
char			*ft_get_home(t_data *data);
// echo.c
int				ft_echo(t_data *data);
void			ft_echo_print(t_data *data, int i, int line);
// env.c
int				ft_env(t_data *data);
// exit.c
void			ft_exit(t_data *data);
int				ft_exit2(t_data *data);
int				is_valid_exit_argument(char *str);
int				ft_ratoi(char *str);

// export1.c
void			bubble_sort(char **env);
int				is_valid_var_name(char *var);
void			export_without_args(t_data *data);
void			update_exp_without_equal(t_data *data, char *str);
int				ft_export(t_data *data);
// export2.c
void			update_env_with_equal(t_data *data, char *str);
void			update_env_with_equal2(t_data *data, char *str, int i);
void			update_exp_with_equal(t_data *data, char *str);
void			update_exp_with_equal2(t_data *data, char *str, int i);
void			valid_var_name(t_data *data, int i);

// pwd.c
int				ft_pwd(void);
// unset.c
int				ft_unset(t_data *data);
void			unset_var_in_env(t_data *data, char *var_name);
void			unset_var_in_exp(t_data *data, char *var_name);

// expand.c
char			*manage_dollar(char *str, t_data *data);

// expand_utils.c
char			*get_env_value(char *str, t_data *data);
void			get_exit_status(t_data *data, int i);

// signals.c
void			signals(void);
void			sig_int(int signal);
int				g_signals(int new);

// make_env.c
void			make_env(t_data *data, char **env);
void			make_exp(t_data *data, char **env);

// parsing.c
void			parsing(t_data *data);

// // parsing_sub_token.c
int				find_words(t_data *data, int *i);
int				number_of_sub_token(t_data *data, int i);
void			sub_token_quotes(t_token *token, t_data *data, int *i,
					int *sub_token_count);
void			analyse_quotes(t_token *token, t_data *data);
void			sub_token_word(t_token *token, t_data *data, int *i,
					int *sub_token_count);
// free.c
void			free_data(t_data *data);
void			free_all_exit(t_data *data, int exit_code);
void	free_sub_token(t_sub_token *sub_token);
void	free_tokens(t_data *data);
void	free_command(t_command *command);
#endif

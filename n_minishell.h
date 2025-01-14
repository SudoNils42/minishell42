/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:14:19 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/14 17:44:23 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_MINISHELL_H
# define N_MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include "./libft/libft.h"


//utils.c
char	*ft_strjoin_with_slash(const char *s1, const char *s2);
char	*ft_strtok(char *str, const char *delim);

#endif

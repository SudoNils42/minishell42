/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:24 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/15 00:16:39 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_question(t_data *data, int *i, char *result)
{
	char	*exit_str;
	char	*tmp;

	exit_str = ft_itoa(data->exit_status);
	tmp = ft_strjoin(result, exit_str);
	free(result);
	result = tmp;
	free(exit_str);
	(*i) += 2;
	return (result);
}

char	*only_dollar(int *i, char *str, char *result)
{
	char	buf[2];
	char	*tmp;

	buf[0] = str[(*i)];
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	result = tmp;
	(*i)++;
	return (result);
}

char	*expand_dollar(t_data *data, int *i, char *str, char *result)
{
	char	*tmp;
	char	*env_val;
	char	*var;
	int		j;

	(*i)++;
	j = (*i);
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var = ft_substr(str, (*i), j - (*i));
	env_val = get_env_value(var, data);
	if (!env_val)
		env_val = ft_strdup("");
	tmp = ft_strjoin(result, env_val);
	free(result);
	result = tmp;
	free(var);
	free(env_val);
	(*i) = j;
	return (result);
}

char	*no_dollar(int *i, char *str, char *result)
{
	char	buf[2];
	char	*tmp;

	buf[0] = str[(*i)];
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	result = tmp;
	(*i)++;
	return (result);
}

char	*manage_dollar(char *str, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			result = dollar_question(data, &i, result);
		else if (str[i] == '$' && (ft_isspace(str[i + 1]) == 1
				|| str[i + 1] == '\0'))
			result = only_dollar(&i, str, result);
		else if (str[i] == '$')
			result = expand_dollar(data, &i, str, result);
		else
			result = no_dollar(&i, str, result);
	}
	return (result);
}

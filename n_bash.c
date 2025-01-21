/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_bash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:26:43 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/21 15:43:32 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

t_token	*tokenize_input(char *input, int *token_count)
{
	char	**raw_tokens;
	t_token	*tokens;
	int		i;

	*token_count = 0;
	raw_tokens = ft_split(input, ' ');
	if (!raw_tokens)
		return (NULL);
	for (i = 0; raw_tokens[i]; i++)
		(*token_count)++;
	tokens = malloc(sizeof(t_token) * (*token_count));
	if (!tokens)
		return (NULL);
	for (i = 0; i < *token_count; i++)
	{
		tokens[i].value = ft_strdup(raw_tokens[i]);
		tokens[i].type = get_token_type(raw_tokens[i]);
		free(raw_tokens[i]);
	}
	free(raw_tokens);
	return (tokens);
}

int	get_token_type(char *token)
{
	if (!token)
		return (-1);
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	return (TOKEN_WORD);
}
int parse_command(t_data *data)
{
    int arg_count;
    int i;
    int capacity;

    arg_count = 0;
    i = data->current_token;
    capacity = 10; // Taille initiale, augmentera si nécessaire

    data->current_cmd = malloc(sizeof(t_command));
    if (!data->current_cmd)
        return (1);

    data->current_cmd->args = malloc(sizeof(char *) * capacity);
    if (!data->current_cmd->args)
    {
        free(data->current_cmd);
        return (1);
    }

    // Initialiser les FDs
     data->current_cmd->input_fd = STDIN_FILENO;
    data->current_cmd->output_fd = STDOUT_FILENO;
    data->current_cmd->pipe_read = data->next_pipe_read; // Utiliser le pipe précédent
    data->current_cmd->pipe_write = -1;
    data->next_pipe_read = -1;

    // Lire les tokens jusqu'à trouver un pipe ou la fin
    while (i < data->token_count)
    {
        if (data->tokens[i].type == TOKEN_PIPE)
            break;

        else if (data->tokens[i].type == TOKEN_REDIRECT_IN)
        {
            if (i + 1 >= data->token_count)
            {
                printf("Syntax error near unexpected token '<'\n");
                return (1);
            }
            i++;
            // Gérer la redirection d'entrée
            data->current_cmd->input_fd = open(data->tokens[i].value, O_RDONLY);
            if (data->current_cmd->input_fd == -1)
            {
                printf("minishell: %s: No such file or directory\n", data->tokens[i].value);
                return (1);
            }
        }

        else if (data->tokens[i].type == TOKEN_REDIRECT_OUT)
        {
            if (i + 1 >= data->token_count)
            {
                printf("Syntax error near unexpected token '>'\n");
                return (1);
            }
            i++;
            // Gérer la redirection de sortie
            data->current_cmd->output_fd = open(data->tokens[i].value,
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (data->current_cmd->output_fd == -1)
            {
                printf("minishell: %s: Cannot create file\n", data->tokens[i].value);
                return (1);
            }
        }

        else if (data->tokens[i].type == TOKEN_WORD)
        {
            // Augmenter la capacité si nécessaire
            if (arg_count >= capacity - 1)
            {
                capacity *= 2;
                char **new_args = realloc(data->current_cmd->args,
                    sizeof(char *) * capacity);
                if (!new_args)
                    return (1);
                data->current_cmd->args = new_args;
            }

            data->current_cmd->args[arg_count] = ft_strdup(data->tokens[i].value);
            arg_count++;
        }

        i++;
    }

    // Mettre le NULL final
    data->current_cmd->args[arg_count] = NULL;

    // Mettre à jour current_token pour le prochain appel
    data->current_token = i;

    // Si aucun argument n'a été trouvé
    if (arg_count == 0)
    {
        free_command(data->current_cmd);
        data->current_cmd = NULL;
        return (1);
    }

    return (0);
}
int execute_command(t_data *data)
{
    int pipe_fd[2];
    char *cmd_path;

    if (!data->current_cmd || !data->current_cmd->args[0])
        return (1);

    // Si on a un pipe après la commande courante, on le crée
    if (data->current_token < data->token_count &&
        data->tokens[data->current_token].type == TOKEN_PIPE)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe failed");
            return (1);
        }
        data->current_cmd->pipe_write = pipe_fd[1];
        data->next_pipe_read = pipe_fd[0];
    }

    cmd_path = find_command_path(data, data->current_cmd->args[0]);
    if (!cmd_path)
    {
        printf("%s: command not found\n", data->current_cmd->args[0]);
        return (1);
    }

    data->pid = fork();
    if (data->pid == 0)
    {
        handle_redirections(data);
        execve(cmd_path, data->current_cmd->args, data->env);
        perror("execve failed");
        exit(1);
    }

    // Stocker le PID pour attendre plus tard
    if (data->pid_count >= data->max_pids)
    {
        data->max_pids = data->max_pids * 2 + 1;
        int *new_pids = realloc(data->all_pids, sizeof(int) * data->max_pids);
        if (!new_pids)
            return (1);
        data->all_pids = new_pids;
    }
    data->all_pids[data->pid_count++] = data->pid;

    // Fermer les descripteurs de fichiers dans le processus parent
    if (data->current_cmd->pipe_read != -1)
        close(data->current_cmd->pipe_read);
    if (data->current_cmd->pipe_write != -1)
        close(data->current_cmd->pipe_write);

    free(cmd_path);
    return (0);
}

char	*find_command_path(t_data *data, char *cmd)
{
	char	**path_dirs;
	char	*path_env;
	char	*full_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	for (i = 0; path_dirs[i]; i++)
	{
		full_path = ft_strjoin_with_slash(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			// Free path_dirs before returning
			for (int j = 0; path_dirs[j]; j++)
				free(path_dirs[j]);
			free(path_dirs);
			return (full_path);
		}
		free(full_path);
	}
	// Free path_dirs before returning NULL
	for (i = 0; path_dirs[i]; i++)
		free(path_dirs[i]);
	free(path_dirs);
	return (NULL);
	data->input = 0;
}

void handle_redirections(t_data *data)
{
    if (data->current_cmd->pipe_read != -1)
    {
        dup2(data->current_cmd->pipe_read, STDIN_FILENO);
        close(data->current_cmd->pipe_read);
    }

    if (data->current_cmd->pipe_write != -1)
    {
        dup2(data->current_cmd->pipe_write, STDOUT_FILENO);
        close(data->current_cmd->pipe_write);
    }

    if (data->current_cmd->input_fd != STDIN_FILENO)
    {
        dup2(data->current_cmd->input_fd, STDIN_FILENO);
        close(data->current_cmd->input_fd);
    }

    if (data->current_cmd->output_fd != STDOUT_FILENO)
    {
        dup2(data->current_cmd->output_fd, STDOUT_FILENO);
        close(data->current_cmd->output_fd);
    }
}

int process_command_line(t_data *data)
{
    int parse_status;

    data->pid_count = 0;
    while (data->current_token < data->token_count)
    {
        parse_status = parse_command(data);
        if (parse_status == 0)
        {
            if (execute_command(data) != 0)
                return (1);
        }
        if (data->current_token < data->token_count &&
            data->tokens[data->current_token].type == TOKEN_PIPE)
        {
            data->current_token++;
        }
    }

    // Attendre la fin de tous les processus
    int i;
    int status;

    i = 0;
    while (i < data->pid_count)
    {
        waitpid(data->all_pids[i], &status, 0);
        i++;
    }

    return (0);
}

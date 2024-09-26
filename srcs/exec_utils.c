/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:47:02 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/25 15:59:15 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_code(int code, t_data *data, char **tmp)
{
	if (data->path)
		free_tab(data->path);
	if (code == 1)
		return (dprintf(2, "command not found\n"), free_tab(tmp), exit(127));
	else if (code == 2)
	{
		dprintf(2, "permission denied: %s\n", tmp[0]);
		return (free_tab(tmp), exit(126));
	}
	else if (code == 3)
	{
		dprintf(2, "no such file or directory: %s\n", tmp[0]);
		return (free_tab(tmp), exit(127));
	}
	else if (code == 4)
	{
		dprintf(2, "minishell: %s: command not found\n", tmp[0]);
		return (free_tab(tmp), exit(127));
	}
	else if (code == 5)
	{
		perror("pipex");
		return (free_tab(tmp), exit(126));
	}
}

char	*cmd(t_data *data, char *command)
{
	char	*str;
	int		i;

	i = 0;
	while (data->path[i])
	{
		str = ft_strjoin(data->path[i], command);
		if (access(str, F_OK | X_OK | R_OK) == 0)
			return (str);
		free(str);
		i++;
	}
	return (NULL);
}

void	ft_execve(t_data *data, char **envp)
{
	char	*path;

	if (!data->cmd->arguments[0] && data->cmd->redirection)
		return ;
	if (!data->cmd->arguments || !data->cmd->arguments[0])
		ft_exit_code(1, data, data->cmd->arguments);
	if (ft_strchr(data->cmd->arguments[0], '/'))
	{
		if (access(data->cmd->arguments[0], F_OK | X_OK | R_OK) == 0)
			execve(data->cmd->arguments[0], data->cmd->arguments, envp);
		else if (access(data->cmd->arguments[0], F_OK) == 0
			&& (access(data->cmd->arguments[0], X_OK | R_OK)))
			ft_exit_code(2, data, data->cmd->arguments);
		else
			ft_exit_code(3, data, data->cmd->arguments);
	}
	path = cmd(data, data->cmd->arguments[0]);
	if (!path)
		ft_exit_code(4, data, data->cmd->arguments);
	execve(path, data->cmd->arguments, envp);
	free(path);
	ft_exit_code(4, data, data->cmd->arguments);
}

int	ft_redirection(t_command *cmd)
{
	int	fd;

	fd = -1;
	while (cmd->redirection)
	{
		if (cmd->redirection->type == REDIR_IN)
			fd = open(cmd->redirection->file, O_RDONLY);
		if (cmd->redirection->type == REDIR_OUT)
			fd = open(cmd->redirection->file, O_WRONLY | O_CREAT | O_TRUNC,
					0666);
		if (cmd->redirection->type == APPEND)
			fd = open(cmd->redirection->file, O_WRONLY | O_CREAT | O_APPEND,
					0666);
		if (fd == -1)
			return (perror("open"), 1);
		if (cmd->redirection->type == REDIR_OUT
			|| cmd->redirection->type == APPEND)
			dup2(fd, STDOUT_FILENO);
		if (cmd->redirection->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		close(fd);
		cmd->redirection = cmd->redirection->next;
	}
	return (0);
}

void	ft_executor(t_data *data, char **env, int i)
{
	if (pipe(data->fd) == -1)
		perror("pipe");
	data->cmd->pid = fork();
	if (data->cmd->pid == -1)
		perror("fork");
	if (data->cmd->pid == 0)
	{
		close(data->fd[0]);
		if (i != 0)
		{
			dup2(data->prev, STDIN_FILENO);
			close(data->prev);
		}
		if (data->cmd->next != NULL)
			dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		if (ft_redirection(data->cmd))
		{
			if (data->path)
				free_tab(data->path);
			free_tab(env);
			clean_all(data);
		}
		ft_execve(data, env);
		free_tab(data->path);
		free_tab(env);
		clean_all(data);
	}
	close(data->fd[1]);
	if (data->prev != -1)
		close(data->prev);
	data->prev = data->fd[0];
}

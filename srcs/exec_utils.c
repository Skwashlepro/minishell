/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:47:02 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/12 20:33:15 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, char **envp, t_command *cmd)
{
	char	*path;

	if (!cmd->arguments && cmd->redirection)
		return ;
	if (ft_strchr(cmd->arguments[0], '/'))
	{
		if (access(cmd->arguments[0], F_OK | X_OK | R_OK) == 0)
			execve(cmd->arguments[0], cmd->arguments, envp);
		else if (access(cmd->arguments[0], F_OK) == 0
			&& (access(cmd->arguments[0], X_OK | R_OK)))
			ft_exit_code(2, data, cmd, envp);
		else
			ft_exit_code(3, data, cmd, envp);
	}
	path = get_cmd(data, cmd->arguments[0]);
	if (!path)
		ft_exit_code(1, data, cmd, envp);
	execve(path, cmd->arguments, envp);
	free(path);
}

int	redirection_file(int fd, t_redir *redirection)
{
	if (redirection->type == HERE_DOC)
		fd = open(redirection->heredoc_name, O_RDONLY);
	if (redirection->type == REDIR_IN)
		fd = open(redirection->file, O_RDONLY);
	else if (redirection->type == REDIR_OUT)
		fd = open(redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirection->type == APPEND)
		fd = open(redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	if (redirection->type == REDIR_OUT || redirection->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	else if (redirection->type == REDIR_IN || redirection->type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_redirection(t_command *cmd)
{
	int		fd;
	t_redir	*redirection;

	fd = -1;
	redirection = cmd->redirection;
	while (redirection)
	{
		if (redirection_file(fd, redirection) == 1)
		{
			if (access(redirection->file, F_OK) != 0)
				ft_printf(2, "minishell: %s: No such file or directory\n",
					redirection->file);
			else
				ft_printf(2, "minishell: %s: Permission denied\n",
					redirection->file);
			return (1);
		}
		redirection = redirection->next;
	}
	return (0);
}

void	exec_child(t_command *cmd, t_data *data, char **env, int i)
{
	if (cmd->pid == 0)
	{
		rl_clear_history();
		close(data->fd[0]);
		if (i != 0)
		{
			dup2(data->prev, STDIN_FILENO);
			close(data->prev);
		}
		if (cmd->next != NULL)
			dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		if (ft_redirection(cmd))
		{
			fork_redir_free(data, env, data->path);
			exit(1);
		}
		ft_execve(data, env, cmd);
		fork_redir_free(data, env, data->path);
		exit(0);
	}
}

void	ft_executor(t_command *cmd, t_data *data, char **env, int i)
{
	if (pipe(data->fd) == -1)
		perror("pipe");
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
	child_signals();
	exec_child(cmd, data, env, i);
	close(data->fd[1]);
	if (data->prev != -1)
		close(data->prev);
	data->prev = data->fd[0];
}

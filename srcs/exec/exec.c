/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/17 21:22:20 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**tab_env(char **tab)
{
	char	*str;
	int		j;

	j = -1;
	str = NULL;
	while (tab[++j])
	{
		str = ft_strdup(tab[j]);
		free(tab[j]);
		if (str)
		{
			tab[j] = ft_strjoin(str, "/");
			free(str);
		}
	}
	return (tab);
}

char	**find_path(t_data *data)
{
	char	**tab;
	t_env	*env;

	tab = NULL;
	env = data->get_env;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			tab = ft_split(env->value, ':');
			if (!tab)
				return (NULL);
			return (tab_env(tab));
		}
		env = env->next;
	}
	return (NULL);
}

static void	ft_wait(t_data *data, t_command *cmd)
{
	while (cmd)
	{
		waitpid(cmd->pid, &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			g_var = WEXITSTATUS(data->exit_status);
		cmd = cmd->next;
	}
}

int	ft_exec(t_command *cmd, t_data *data)
{
	t_command	*tmp;
	char		**env;
	int			i;

	i = 0;
	env = NULL;
	data->prev = -1;
	init_exec(data, &env, &data->path);
	tmp = cmd;
	if (data->heredoc)
		if (run_heredoc(cmd, data))
			return (free_exec(env, data->path), 130);
	while (cmd)
	{
		if (!i && nb_cmd(cmd) == 1)
			if (ft_onebuiltin(data, cmd->arguments, env))
				return (free_exec(env, data->path), data->exit_status);
		ft_executor(cmd, data, env, i++);
		cmd = cmd->next;
	}
	close(data->fd[0]);
	ft_wait(data, tmp);
	ft_signal();
	free_exec(env, data->path);
	return (data->exit_status);
}

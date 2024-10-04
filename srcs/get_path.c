/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/04 20:56:00 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_path(t_env *env)
{
	char	*str;
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tab = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			tab = ft_split(env->value, ':');
			while (tab[++j])
			{
				str = ft_strdup(tab[j]);
				free(tab[j]);
				tab[j] = ft_strjoin(str, "/");
				free(str);
			}
			return (tab);
		}
		env = env->next;
	}
	return (NULL);
}

void	unlink_file(t_command *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->heredoc_name)
			if (access(tmp->heredoc_name, F_OK | X_OK | R_OK) == 0)
				unlink(tmp->heredoc_name);
		tmp = tmp->next;
	}
}

int	nb_cmd(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_wait(t_data *data, t_command *cmd)
{
	dprintf(2, "g_var: %d\n", g_var);
	while (cmd)
	{
		waitpid(cmd->pid, &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			g_var = WEXITSTATUS(data->exit_status);
		unlink_file(cmd);
		cmd = cmd->next;
	}
	dprintf(2, "g_var after: %d\n", g_var);
}

void	check_heredoc(t_command *cmd, t_data *data)
{
	t_redir	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			ft_here_doc(tmp, data);
			data->heredoc--;
		}
		tmp = tmp->next;
	}
}

void	run_heredoc(t_command *cmd, t_data *data)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		check_heredoc(tmp, data);
		tmp = tmp->next;
	}
}

int	ft_exec(t_command *cmd, t_data *data)
{
	t_env		*env_lst;
	t_command	*tmp;
	char		**env;
	int			i;

	i = 0;
	env = env_to_tab(data);
	env_lst = data->get_env;
	data->path = find_path(env_lst);
	tmp = cmd;
	if (data->heredoc)
		run_heredoc(cmd, data);
	while (cmd)
	{
		ft_executor(cmd, data, env, i++);
		cmd = cmd->next;
	}
	ft_wait(data, tmp);
	ft_signal();
	close(data->fd[0]);
	free_tab(env);
	free_tab(data->path);
	return (data->exit_status);
}

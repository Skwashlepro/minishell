/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/28 18:09:45 by tpassin          ###   ########.fr       */
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

void	ft_wait(t_data *data, t_command *cmd)
{
	while (cmd)
	{
		waitpid(cmd->pid, &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		cmd = cmd->next;
	}
}

void	run_heredoc(t_command *cmd, t_data *data)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redirection)
		{
			if (tmp->redirection->type == HERE_DOC)
			{
				ft_here_doc(tmp, tmp->redirection->file, data);
				free(tmp->redirection->file);
				tmp->redirection->file = tmp->redirection->heredoc_name;
				data->heredoc--;
			}
		}
		tmp = tmp->next;
	}
	cmd = tmp;
}

int	ft_exec(t_command *cmd, t_data *data)
{
	t_env		*env_lst;
	t_command	*tmp;
	char		**env;
	int			i;

	i = 0;
	data->prev = -1;
	env = env_to_tab(data);
	env_lst = data->get_env;
	data->path = find_path(env_lst);
	tmp = cmd;
	if (data->heredoc)
		run_heredoc(cmd, data);
	while (cmd)
	{
		ft_executor(cmd, data, env, i);
		cmd = cmd->next;
		i++;
	}
	ft_wait(data, tmp);
	close(data->fd[0]);
	free_tab(env);
	free_tab(data->path);
	return (data->exit_status);
}

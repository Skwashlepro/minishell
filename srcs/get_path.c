/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/08 18:10:04 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_path(t_data *data)
{
	char	*str;
	char	**tab;
	int		i;
	int		j;
	t_env	*env;

	i = 0;
	j = -1;
	tab = NULL;
	env = data->get_env;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			tab = ft_split(env->value, ':');
			if (!tab)
				return (NULL);
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
		env = env->next;
	}
	return (NULL);
}

void	ft_wait(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			g_var = WEXITSTATUS(data->exit_status);
		unlink_file(cmd);
		cmd = cmd->next;
		i++;
	}
}

void	run_heredoc(t_command *cmd, t_data *data)
{
	t_command	*tmp;
	t_redir		*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->redirection;
		while (redir)
		{
			if (redir->type == HERE_DOC)
			{
				ft_here_doc(redir, data);
				data->heredoc--;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

int	ft_exec(t_command *cmd, t_data *data)
{
	t_command	*tmp;
	char		**env;
	int			i;

	i = 0;
	if (data->heredoc > 15)
	{
		ft_printf(2, "minishell: maximum here-document count exceeded\n");
		clean_all(data);
	}
	env = env_to_tab(data);
	data->path = find_path(data);
	if (!data->path)
		return (free_tab(env), -1);
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

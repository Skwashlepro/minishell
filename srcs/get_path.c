/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/25 18:37:11 by tpassin          ###   ########.fr       */
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

int	ft_exec(t_data *data)
{
	t_env		*env_lst;
	char		**env;
	int			i;

	// pid_t	pid;
	i = 0;
	data->prev = -1;
	env = env_to_tab(data);
	env_lst = data->get_env;
	data->path = find_path(env_lst);
	t_command *head = data->cmd;
	while (data->cmd)
	{
		ft_executor(data, env, i);
		data->cmd = data->cmd->next;
		i++;
	}
	close(data->fd[0]);
	data->cmd = head;
	while (data->cmd)
	{
		waitpid(data->cmd->pid, &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		data->cmd = data->cmd->next;
	}
	free_tab(env);
	free_tab(data->path);
	return (data->exit_status);
}

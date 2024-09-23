/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/23 18:52:55 by tpassin          ###   ########.fr       */
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

int	ft_exec(t_command *command, t_data *data)
{
	t_env	*env;
	pid_t	pid;

	int i = 0;
	(void)command;
	env = data->get_env;
	data->path = find_path(env);
	while (++i < size_command(data->cmd))
	{
		ft_executor(data, &i, data->env);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		execve(data->cmd->arguments[0], data->cmd->arguments, data->env);
	}
	waitpid(pid, &data->exit_status, 0);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	return (data->exit_status);
}

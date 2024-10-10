/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:53 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/11 00:04:45 by luctan           ###   ########.fr       */
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
<<<<<<< HEAD:srcs/get_path.c
	int		j;
	t_env	*env;

	j = -1;
=======
	int		i;
	t_env	*env;

	i = 0;
>>>>>>> main:srcs/exec.c
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
			if (ft_onebuiltin(data, cmd->arguments))
				return (free_tab(env), free_tab(data->path), data->exit_status);
		ft_executor(cmd, data, env, i++);
		cmd = cmd->next;
	}
	ft_wait(data, tmp);
	ft_signal();
	close(data->fd[0]);
<<<<<<< HEAD:srcs/get_path.c
	free_tab(env);
	free_tab(data->path);
	// printf("this : %i\n", data->exit_status);
=======
	free_exec(env, data->path);
>>>>>>> main:srcs/exec.c
	return (data->exit_status);
}

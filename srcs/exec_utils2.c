/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:05:34 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/09 15:41:15 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_code(int code, t_data *data, t_command *cmd, char **envp)
{
	if (data->path)
		free_tab(data->path);
	if (code == 1)
		return (ft_printf(2, "minishell: %s: command not found\n",
				cmd->arguments[0]), fork_clean(data, envp), exit(127));
	else if (code == 2)
		return (fork_clean(data, envp), ft_printf(2,
				"minishell:%s: Permission denied\n", cmd->arguments[0]),
			exit(126));
	else if (code == 3)
	{
		ft_printf(2, "No such file or directory: %s\n", cmd->arguments[0]);
		return (fork_clean(data, envp), exit(127));
	}
}

char	*get_cmd(t_data *data, char *command)
{
	char	*str;
	int		i;

	i = 0;
	while (data->path && data->path[i])
	{
		str = ft_strjoin(data->path[i], command);
		if (access(str, F_OK | X_OK | R_OK) == 0)
			return (str);
		free(str);
		i++;
	}
	return (NULL);
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

void	init_exec(t_data *data, char ***env, char ***path)
{
	if (data->heredoc > 15)
	{
		ft_printf(2, "minishell: maximum here-document count exceeded\n");
		clean_all(data);
	}
	*env = env_to_tab(data);
	*path = find_path(data);
}

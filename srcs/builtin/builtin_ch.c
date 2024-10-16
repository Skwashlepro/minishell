/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:41:54 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 01:47:43 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_bank(int forked)
{
	char	**bank;
	int		i;

	i = -1;
	bank = malloc(sizeof(char **) * 8);
	if (forked)
	{
		bank[++i] = ft_strdup("echo");
		bank[++i] = ft_strdup("env");
		bank[++i] = ft_strdup("pwd");
		bank[++i] = ft_strdup("cd");
		bank[++i] = ft_strdup("exit");
		bank[++i] = ft_strdup("export");
		bank[++i] = ft_strdup("unset");
	}
	else
	{
		bank[++i] = ft_strdup("cd");
		bank[++i] = ft_strdup("exit");
		bank[++i] = ft_strdup("export");
		bank[++i] = ft_strdup("unset");
	}
	bank[++i] = 0;
	return (bank);
}

char	*finder(char *cmd, int forked)
{
	char	**comp;
	char	*found;
	int		i;

	i = 0;
	found = NULL;
	comp = cmd_bank(forked);
	while (comp[i] && !found)
	{
		if (!ft_strcmp(cmd, comp[i]))
			found = ft_strdup(comp[i]);
		i++;
	}
	free_tab(comp);
	return (found);
}

int	ft_onebuiltin(t_data *data, char **cmd, char **env)
{
	char	*command;

	data->exit_status = 0;
	if (!cmd || !cmd[0])
		return (0);
	command = finder(cmd[0], 0);
	if (command == NULL)
		return (0);
	else if (!cmd[1] && !ft_strcmp(command, "export"))
		return (free_array(command), 0);
	else if (!ft_strcmp(command, "cd"))
		data->exit_status = cd(data, cmd);
	else if (!ft_strcmp(command, "exit"))
		return (free_array(command), ft_exit(cmd, data, env), 1);
	else if (!ft_strcmp(command, "export"))
		export(data, cmd);
	else if (!ft_strcmp(command, "unset"))
		unset(data, cmd);
	if (command)
		free_array(command);
	return (1);
}

int	ft_builtin(t_data *data, char **cmd, char **envp)
{
	char	*command;

	data->exit_status = 0;
	if (!cmd || !cmd[0])
		return (0);
	command = finder(cmd[0], 1);
	if (command == NULL)
		return (0);
	else if (!ft_strcmp(command, "exit"))
		return (free_array(command), ft_exit(cmd, data, envp), 1);
	else if (!ft_strcmp(command, "export"))
		export(data, cmd);
	else if (!ft_strcmp(command, "unset"))
		unset(data, cmd);
	else if (!ft_strcmp(command, "echo"))
		echo(cmd);
	else if (!ft_strcmp(command, "env"))
		env(data);
	else if (!ft_strcmp(command, "pwd"))
		pwd(data);
	if (command)
		free_array(command);
	return (1);
}

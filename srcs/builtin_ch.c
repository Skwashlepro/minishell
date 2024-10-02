/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:41:54 by luctan            #+#    #+#             */
/*   Updated: 2024/10/02 20:07:02 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *uncapitalizer(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			cmd[i] += 32;
		i++;
	}
	return (cmd);
}

char **cmd_bank ()
{
	char **bank;
	int	i;
	
	i = -1;
	bank = malloc(sizeof(char **) * 8);
	bank[++i] = ft_strdup("cd");
	bank[++i] = ft_strdup("echo");
	bank[++i] = ft_strdup("env");
	bank[++i] = ft_strdup("exit");
	bank[++i] = ft_strdup("export");
	bank[++i] = ft_strdup("pwd");
	bank[++i] = ft_strdup("unset");
	bank[++i] = 0;
	return (bank);
}

char	*finder(char *cmd)
{
	char **comp;
	char *found;
	int	i;

	i = 0;
	found = NULL;
	comp = cmd_bank();
	cmd = uncapitalizer(cmd);
	while (comp[i] && !found)
	{
		if (!ft_strcmp(cmd, comp[i]))
			found = ft_strdup(comp[i]);
		i++;
	}
	free_tab(comp);
	return (found);
}

int	ft_builtin(t_data *data, char **cmd)
{
	char *command;
	
	command = finder(cmd[0]);
	dprintf(2, "%s\n", command);
	if (command == NULL)
		return (1);
	if (!ft_strcmp(command, "cd"))
	{
		if (cmd[2])
			return ((void)printf("%s%s\n", "cd: string not in pwd: ", cmd[1]), 1);
		cd(data, cmd[1]);
	}
	else if (!ft_strcmp(command, "echo"))
		echo(cmd + 1);
	else if (!ft_strcmp(command, "env"))
		env(data);
	else if (!ft_strcmp(command, "exit"))
		ft_exit(cmd, data);
	else if (!ft_strcmp(command, "export"))
		export(data, cmd + 1);
	else if (!ft_strcmp(command, "pwd"))
		pwd(data);
	else if (!ft_strcmp(command, "unset"))
		unset(data, cmd[1]);
	free_array(command);
	return (1);
}

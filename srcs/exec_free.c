/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:07:11 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/30 13:47:50 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_clean(t_data *data, char **envp)
{
	t_command *cmd;

	cmd = data->cmd;
	clean_cmd(cmd);
	free_node(data->head);
	if (data->prompt)
		free(data->prompt);
	free_tab(envp);
	if (data->get_env)
		free_env(data->get_env);
}

void	fork_redir_free(t_data *data, char **env, char **path)
{
	if (env)
		free_tab(env);
	if (path)
		free_tab(path);
	clean_all(data);
}

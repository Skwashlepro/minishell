/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:07:11 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/11 00:04:30 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_clean(t_data *data, char **env)
{
	if (env)
		free_tab(env);
	if (data->get_env)
		free_env(data->get_env);
	ft_clean(data);
}

void	fork_redir_free(t_data *data, char **env, char **path)
{
	if (env)
		free_tab(env);
	if (path)
		free_tab(path);
	if (data->get_env)
		free_env(data->get_env);
	ft_clean(data);
}

void	free_exec(char **env, char **path)
{
	if (env)
		free_tab(env);
	if (path)
		free_tab(path);
}

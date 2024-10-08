/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:07:11 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/08 16:31:47 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_clean(t_data *data, char **env)
{
	if (env)
		free_tab(env);
	ft_clean(data);
	free_env(data->get_env);
}

void	fork_redir_free(t_data *data, char **env, char **path)
{
	if (env)
		free_tab(env);
	if (path)
		free_tab(path);
	ft_clean(data);
	free_env(data->get_env);
	exit(1);
}

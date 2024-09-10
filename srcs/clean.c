/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:09:07 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/10 18:04:08 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_data *data)
{
	t_token	*tmp;

	while (data->head)
	{
		tmp = data->head->next;
		free(data->head->str);
		free(data->head);
		data->head = tmp;
	}
	data->head = NULL;
}

void	free_env(t_data *data)
{
	t_env	*tmp;
	
	while (data->get_env)
	{
		tmp = data->get_env->next;
		free(data->get_env->key);
		free(data->get_env->value);
		free(data->get_env);
		data->get_env = tmp;
	}
	data->get_env = NULL;
}

void	ft_clean(t_data *data)
{
	if (data->env)
		free_tab(data->env);
	if (data->head)
		free_node(data);
	if (data->get_env)
		free_env(data);
	rl_clear_history();
}

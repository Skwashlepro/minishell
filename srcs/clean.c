/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:09:07 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/04 15:25:11 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_data **data)
{
	t_token	*tmp;

	while ((*data)->head)
	{
		tmp = (*data)->head->next;
		free((*data)->head->str);
		free((*data)->head);
		(*data)->head = tmp;
	}
	(*data)->head = NULL;
}

void	free_env(t_data **data)
{
	t_env	*tmp;

	while ((*data)->get_env)
	{
		tmp = (*data)->get_env->next;
		free((*data)->get_env->key);
		free((*data)->get_env->value);
		free((*data)->get_env);
		(*data)->get_env = tmp;
	}
	(*data)->get_env = NULL;
}

void	ft_clean(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->env)
		free_tab(data->env);
	if (data->head)
		free_node(&data);
}

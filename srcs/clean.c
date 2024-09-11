/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:09:07 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/11 17:28:03 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->str);
		free(head);
		head = tmp;
	}
	head = NULL;
}

void	free_env(t_env *get_env)
{
	t_env	*tmp;
	
	while (get_env)
	{
		tmp = get_env->next;
		free(get_env->key);
		free(get_env->value);
		free(get_env);
		get_env = tmp;
	}
	get_env = NULL;
}

void	ft_clean(t_data *data)
{
	if (data->head)
		free_node(data->head);
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

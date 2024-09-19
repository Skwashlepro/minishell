/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:09:07 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/19 15:50:05 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->str)
			free(head->str);
		free(head);
		head = tmp;
	}
}

void	free_env(t_env *get_env)
{
	t_env	*tmp;

	while (get_env)
	{
		tmp = get_env->next;
		if (get_env->key)
			free(get_env->key);
		if (get_env->value)
			free(get_env->value);
		free(get_env);
		get_env = tmp;
	}
}

void	clean_cmd(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->arguments)
			free_tab(cmd->arguments);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_clean(t_data *data)
{
	if (data->cmd)
	{
		clean_cmd(data->cmd);
		data->cmd = NULL;
	}
	if (data->head)
	{
		free_node(data->head);
		data->head = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

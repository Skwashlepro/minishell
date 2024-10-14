/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:09:07 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/12 19:10:33 by tpassin          ###   ########.fr       */
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

void	free_redir(t_redir *redirection)
{
	t_redir	*tmp;

	while (redirection)
	{
		tmp = redirection->next;
		if (redirection->file)
			free(redirection->file);
		if (redirection->heredoc_name)
			free(redirection->heredoc_name);
		free(redirection);
		redirection = tmp;
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
		if (cmd->redirection)
			free_redir(cmd->redirection);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_clean(t_data *data)
{
	data->heredoc = 0;
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

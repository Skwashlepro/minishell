/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:21:08 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/18 01:43:57 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	type_redirection(t_token *token)
{
	if (ft_strcmp(token->str, "<<") == 0)
		return (HERE_DOC);
	if (ft_strcmp(token->str, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(token->str, ">>") == 0)
		return (APPEND);
	return (REDIR_OUT);
}

int	add_redirection(t_token *token, t_data *data, t_command *command)
{
	t_redir	*redir;
	char	*str;

	str = NULL;
	redir = malloc(sizeof(t_redir));
	if (!redir || !token || !token->str)
		return (1);
	redir->type = type_redirection(token);
	if (!token->next || !token->next->str)
		return (1);
	str = ft_expand(data, token->next->str, redir->type,
			token->next->nb_quotes);
	if (!str)
		return (free(redir), 1);
	redir->file = str;
	redir->heredoc_name = NULL;
	redir->next = NULL;
	redirection_addback(&command->redirection, redir);
	return (0);
}

bool	add_word(t_token *token, t_command *command, t_data *data)
{
	char	*str;

	if ((only_quote(token->str)) && !command->arguments)
	{
		command->arguments = ft_join_tab(command->arguments,
				ft_strdup(token->str));
		return (false);
	}
	str = ft_expand(data, token->str, token->type, token->nb_quotes);
	if (!str)
		return (true);
	if (!*str)
	{
		free(str);
		return (false);
	}
	command->arguments = ft_join_tab(command->arguments, str);
	if (command->arguments)
		return (false);
	return (true);
}

int	parse_token(t_data *data, t_token **token, t_command *command)
{
	if (*token && (*token)->type == REDIRECTION)
	{
		if (add_redirection(*token, data, command))
			return (1);
		*token = (*token)->next;
	}
	else if (*token && (*token)->type == WORD)
		if (add_word(*token, command, data))
			return (1);
	*token = (*token)->next;
	return (0);
}

t_command	*parsing(t_data *data)
{
	t_token		*token;
	t_command	*tmp;
	t_command	*copy;

	tmp = data->cmd;
	copy = data->cmd;
	token = data->head;
	while (token)
	{
		tmp = malloc(sizeof(t_command));
		if (!tmp)
			return (NULL);
		ft_memset(tmp, 0, sizeof(t_command));
		while (token && token->type != PIPE)
		{
			if (parse_token(data, &token, tmp))
				return (NULL);
		}
		if (token)
			token = token->next;
		command_addback(&copy, tmp);
	}
	return (copy);
}

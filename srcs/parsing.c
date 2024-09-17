/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:21:08 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/16 15:37:16 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	type_redirection(t_token *token)
{
	if (ft_strncmp(token->str, "<<", ft_strlen(token->str)) == 0)
		return (HERE_DOC);
	if (ft_strncmp(token->str, "<", ft_strlen(token->str)) == 0)
		return (REDIR_IN);
	if (ft_strncmp(token->str, ">>", ft_strlen(token->str)) == 0)
		return (APPEND);
	return (REDIR_OUT);
}

int	add_redirection(t_token *token, t_data *data)
{
	t_redir	*redir;
	char	*str;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (1);
	redir->type = type_redirection(token);
	str = ft_expand(data, token->str, redir->type, token->nb_quotes);
	if (!str)
		return (free(redir), 1);
	redir->file = str;
	redir->next = NULL;
	return (0);
}

bool	add_word(t_token *token, t_command *command, t_data *data)
{
	command->arguments = ft_join_tab(command->arguments, ft_expand(data, token->str,
				token->type, token->nb_quotes));
	if (command->arguments)
		return (false);
	return (true);
}

int	parse_token(t_data *data, t_token **token, t_command *command)
{
	if (*token && (*token)->type == REDIRECTION)
	{
		if (add_redirection(*token, data))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:21:08 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/10 17:38:23 by tpassin          ###   ########.fr       */
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

int	add_redirection(t_token *token, t_data *data, t_command *command)
{
	t_redir	*redir;
	char	*str;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (1);
	redir->type = type_redirection(token);
	str = ft_expand(data, token->str);
	if (!str)
		return (free(redir), 1);
	redir->file = str;
	redir->next = NULL;
	return (0);
	
}

int	add_word(t_token *token, t_data *data, t_command *command)
{
	char **args;

	
}

int	parse_token(t_data *data, t_token *token, t_command *command)
{
	if (token && token->type == REDIRECTION)
	{
		if (add_redirection(token, data, command))
			return (1);
		token = token->next;
	}
	else if (token && token->type == WORD)
		if (add_word(token, data, command))
			return (1);
	token = token->next;
	return (0);
}

int	parsing(t_data *data)
{
	t_command *command;
	t_token *token;

	token = data->head;
	while (token)
	{
		command = malloc(sizeof(t_command));
		ft_memset(command, 0, sizeof(t_command));
		while (token && token->type != PIPE)
		{
			if (parse_token(data, token, command))
				return (1);
		}
		if (token)
			token = token->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:14:16 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/16 18:32:13 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **token_head, t_token_type type, char *str)
{
	t_token	*token;
	t_token	*last_token;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->next = NULL;
	token->str = ft_strdup(str);
	token->type = type;
	if (!(*token_head))
	{
		*token_head = token;
		token->prev = NULL;
	}
	else
	{
		last_token = last_node(*token_head);
		last_token->next = token;
		token->prev = last_token;
	}
}

t_token	*last_node(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

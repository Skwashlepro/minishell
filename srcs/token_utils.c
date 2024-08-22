/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:14:16 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/22 19:31:11 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_token(t_token **token_head, t_token_type type, char *str)
{
	t_token	*token;
	t_token	*last_token;

	if (!str)
		return ;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:14:16 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/27 14:55:30 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_node(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	lst_size(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	add_token(t_token **token_head, t_token_type type, char *str,
		int nb_quotes)
{
	t_token	*token;
	t_token	*last_token;

	if (!str)
		return ;
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(str));
	token->str = ft_strdup(str);
	token->type = type;
	token->nb_quotes = nb_quotes;
	token->next = NULL;
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

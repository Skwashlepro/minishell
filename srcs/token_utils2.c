/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:14:18 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/07 21:01:23 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	add_type_node(t_token **head, char *str, t_data *data)
// {
// 	t_token	*last;

// 	if (!(*head))
// 		add_token(head, CMD, str, data);
// 	else
// 	{
// 		last = last_node(*head);
// 		if (last->type == APPEND || last->type == REDIR_OUT)
// 			add_token(head, OUTFILE, str, data);
// 		else if (last->type == HERE_DOC)
// 			add_token(head, LIMITER, str, data);
// 		else if (last->type == REDIR_IN)
// 			add_token(head, INFILE, str, data);
// 		else if (last->type == CMD)
// 			add_token(head, ARG, str, data);
// 		else if (last->type == PIPE)
// 			add_token(head, CMD, str, data);
//         else
//             add_token(head, ARG, str, data);
// 	}
// 	data->count = 0;
// }

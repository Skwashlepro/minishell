/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/27 18:40:03 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstnew(char *env)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_substr(env, 0, ft_strchri(env, '='));
	new_node->value = ft_substr(env, ft_strchri(env, '='),
			ft_strlen(env));
	new_node->next = NULL;
	return (new_node);
}

void	get_env(t_data *data)
{
	t_env	*new;
	int		i;

	i = 0;
	while (i < 1)
		new = lstnew(data->env[i++]);
	while (new)
	{
		printf("%s", new->key);
		printf("%s\n", new->value);
        new = new->next;
	}
}

// void   lst_addback(t_env **node, t_env *new)
// {
// 	t_env *last;

//     if (node)
//     {
//         if (!*node)
//             *node = new;
//         else
//         {
//             last = lstlast(*(node));
// 			last->next = new;
//             last->prev = last;
//         }
//     }
// }

// int get_env(t_data *data)
// {
// }

// tab = ["USER=mgamil"] lst = key = "USER" value = "mgamil" next
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/26 17:33:10 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *lstnew(char *str)
{
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->name = ft_strdup(str);
    new_node->next = NULL;
    return (new_node);
}

void   lst_addback(t_env **node, t_env *new)
{
	t_env *last;

    if (node)
    {
        if (!*node)
            *node = new;
        else
        {
            last = lstlast(*(node));
			last->next = new;
            last->prev = last;
        }
    }
}

int get_env(t_data *data)
{
    int i;

    while (data->env[i])
        lst_addback(&data->get_env, lstnew(data->env[i++]));

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:09:07 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/30 20:39:31 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_node(t_data **data)
{
    t_token *tmp;

    while ((*data)->head)
    {
        tmp = (*data)->head->next;
        free((*data)->head);
        (*data)->head = tmp;
    }
    (*data)->head = NULL;
}

void free_env(t_data **data)
{
    t_env *tmp;

    while((*data)->get_env)
    {
        tmp = (*data)->get_env->next;
        free((*data)->get_env);
        (*data)->get_env = tmp;
    }
    (*data)->get_env = NULL;
}

void ft_clean(t_data *data)
{
    free(data->prompt);
    free(data->env);
    free_env(&data);
    free_node(&data);
}
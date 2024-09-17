/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:32:03 by luctan            #+#    #+#             */
/*   Updated: 2024/09/17 16:45:32 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unset(t_data *data, char *var)
{
	t_env *tmp;
	
	tmp = data->get_env;
	while (tmp->key != var && tmp)
		tmp = tmp->next;
	if (tmp->key == var)
	{
		while (data->get_env->next != tmp)
			data->get_env = data->get_env->next;
		if (tmp->next)
			data->get_env->next = tmp->next;
		else
			data->get_env->next = NULL;
		free_array(tmp->key);
		free_array(tmp->value);
	}
	return ;
}

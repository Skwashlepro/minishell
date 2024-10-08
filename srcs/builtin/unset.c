/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:32:03 by luctan            #+#    #+#             */
/*   Updated: 2024/10/08 19:29:45 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset(t_data **data, char *var)
{
	t_env *tmp;
	t_env *fst;
	
	tmp = (*data)->get_env;
	fst = (*data)->get_env;
	if (!var)
		return (1);
	while (ft_strcmp(tmp->key, var) && tmp)
		tmp = tmp->next;
	if (!ft_strcmp(tmp->key, var))
	{
		while ((*data)->get_env->next && (*data)->get_env->next != tmp)
			(*data)->get_env = (*data)->get_env->next;
		if (tmp->next)
			(*data)->get_env->next = tmp->next;
		else
			(*data)->get_env->next = NULL;
		free_array(tmp->key);
		free_array(tmp->value);
		free(tmp);
	}
	(*data)->get_env = fst;
	return (0);
}

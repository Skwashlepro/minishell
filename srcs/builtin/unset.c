/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:32:03 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 00:47:29 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_unset(t_env *tmp)
{
	free_array(tmp->key);
	free_array(tmp->value);
	free(tmp);
}

void	unset(t_data **data, char **var)
{
	t_env	*tmp;
	t_env	*fst;
	int		i;

	i = 0;
	fst = (*data)->get_env;
	if (!var[1] || !(*data)->get_env)
		return ;
	while (var[++i])
	{
		tmp = (*data)->get_env;
		while (ft_strcmp(tmp->key, var[i]) && tmp->next)
			tmp = tmp->next;
		if (!ft_strcmp(tmp->key, var[i]))
		{
			while ((*data)->get_env->next && (*data)->get_env->next != tmp)
				(*data)->get_env = (*data)->get_env->next;
			if (tmp->next)
				(*data)->get_env->next = tmp->next;
			else
				(*data)->get_env->next = NULL;
			free_unset(tmp);
		}
	}
	(*data)->get_env = fst;
	return ;
}

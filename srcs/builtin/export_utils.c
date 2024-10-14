/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:34:50 by luctan            #+#    #+#             */
/*   Updated: 2024/10/14 20:26:59 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_paste(t_env *node, char *args, int j)
{
	node->value = ft_strdup(args + j);
	node->equal = 1;
	node->next = NULL;
}

int	valid_id(char *args)
{
	if (!ft_isalpha(args[0]))
	{
		ft_printf(2, "minishell$: export: '%s': not a valid identifier\n", args);
		return (0);
	}
	return (1);
}

void	node_free(t_env *node)
{
	if (node)
	{
		if (node->value)
			free_array(node->value);
		if (node->key)
			free_array(node->key);
		free(node);
	}
}

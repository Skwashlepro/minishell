/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:34:50 by luctan            #+#    #+#             */
/*   Updated: 2024/10/14 18:51:14 by luctan           ###   ########.fr       */
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

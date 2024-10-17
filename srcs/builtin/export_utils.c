/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:34:50 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 01:45:16 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstrn(char *str, int i)
{
	int	j;

	j = -1;
	while (str[i] != '=' && str[i])
		i++;
	while (str[++j] && j != i)
		write(2, &str[j], 1);
}

void	value_paste(t_env *node, char *args, int j)
{
	node->value = ft_strdup(args + j);
	node->equal = 1;
	node->next = NULL;
}

int	valid_id(t_data **data, char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]))
	{
		ft_printf(2, "minishell$: export: '");
		ft_putstrn(args, i);
		ft_printf(2, "': not a valid identifier\n");
		(*data)->exit_status = 1;
		return (0);
	}
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && ft_isascii(args[i]))
		{
			ft_printf(2, "minishell$: export: '");
			ft_putstrn(args, i);
			ft_printf(2, "': not a valid identifier\n");
			(*data)->exit_status = 1;
			return (0);
		}
		i++;
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

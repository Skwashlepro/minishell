/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 05:40:22 by luctan            #+#    #+#             */
/*   Updated: 2024/10/14 18:53:08 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_values(char *value, char *key)
{
	if (key)
		free_array(key);
	if (value)
		free_array(key);
}

t_env	*new_env(void)
{
	t_env	*new;
	t_env	*new_node;
	char	*key;
	char	*value;

	new = NULL;
	key = ft_strdup("PWD");
	value = NULL;
	value = getcwd(value, 0);
	new_node = lstnew(key, value);
	if (!new_node)
		return (free_values(value, key), NULL);
	lst_addback(&new, new_node);
	key = ft_strdup("SHLVL");
	value = ft_strdup("1");
	new_node = lstnew(key, value);
	if (!new_node)
		return (free_values(value, key), NULL);
	lst_addback(&new, new_node);
	return (new);
}

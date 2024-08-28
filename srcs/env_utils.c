/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/28 16:39:09 by tpassin          ###   ########.fr       */
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
	new_node->value = ft_substr(env, ft_strchri(env, '=') + 1, ft_strlen(env
				+ 1));
	new_node->equal = 1;
	new_node->next = NULL;
	return (new_node);
}

t_env	*lst_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lst_addback(t_env **node, t_env *new)
{
	t_env	*last;

	if (node)
	{
		if (!(*node))
			*node = new;
		else
		{
			last = lst_env(*node);
			last->next = new;
		}
	}
}

void	get_env(t_data *data)
{
	t_env	*new;
	int		i;

	i = 0;
	new = NULL;
	while (data->env[i])
	{
		if (!new)
			new = lstnew(data->env[i]);
		else
		{
			lst_addback(&new, lstnew(data->env[i]));
		}
		i++;
	}
	while (new)
	{
		printf("%s ", new->key);
		printf("%s\n", new->value);
		new = new->next;
	}
}

// int get_env(t_data *data)
// {
// }

// tab = ["USER=mgamil"] lst = key = "USER" value = "mgamil" next
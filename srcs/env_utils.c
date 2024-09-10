/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/10 18:11:09 by luctan           ###   ########.fr       */
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
	if (!new_node->key)
			return (free(new_node->key), NULL);
	new_node->value = ft_substr(env, ft_strchri(env, '=') + 1, ft_strlen(env)
			- (ft_strchri(env, '=') + 1));
	if ( !new_node->value)
		return (free(new_node->value), NULL);
	new_node->equal = 1;
	new_node->next = NULL;
	return (new_node);
}

t_env	*lst_env(t_env *env)
{
	t_env	*tmp;

	if (!env || !env->next)
		return (NULL);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lst_addback(t_env **node, t_env *new)
{
	t_env	*last;

	if (node && new)
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

void	copy_env(t_data *data)
{
	t_env	*new;
	t_env	*new_node;
	int		i;

	i = 0;
	new = NULL;
	new_node = NULL;
	while (data->env[i])
	{
		new_node = lstnew(data->env[i]);
		if (!new_node)
			return ;
		if (!new)
			new = new_node;
		else
			lst_addback(&new, new_node);
		i++;
	}
	data->get_env = new;
}

char	**env_to_tab(t_data *data)
{
	t_env	*copy;
	char	**tab;
	int		i;

	i = lst_size(data->get_env);
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	copy = data->get_env;
	i = 0;
	while (copy)
	{
		tab[i] = ft_strjoin(copy->key, "=");
		tab[i] = ft_strjoin(tab[i], copy->value);
		copy = copy->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

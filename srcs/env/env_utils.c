/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/25 15:38:58 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_value(char *key, char *value)
{
	if (key)
	{
		free(key);
		key = NULL;
	}
	if (value)
	{
		free(value);
		value = NULL;
	}
}

t_env	*lstnew(char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = key;
	if (!new_env->key)
		return (free_value(key, value), NULL);
	new_env->value = value;
	if (!new_env->value)
		return (free_value(key, value), NULL);
	new_env->equal = 1;
	new_env->next = NULL;
	return (new_env);
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
		if ((*node) == NULL)
			*node = new;
		else
		{
			last = lst_env(*node);
			last->next = new;
		}
	}
}

t_env	*copy_env(char **envp)
{
	t_env	*new;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		i;

	i = -1;
	new = NULL;
	new_node = NULL;
	while (envp[++i])
	{
		key = ft_substr(envp[i], 0, ft_strchri(envp[i], '='));
		value = ft_substr(envp[i], (ft_strchri(envp[i], '=') + 1),
				ft_strlen(envp[i]) - ft_strchri(envp[i], '='));
		new_node = lstnew(key, value);
		if (!new_node)
			return (free_value(key, value), NULL);
		lst_addback(&new, new_node);
	}
	return (new);
}

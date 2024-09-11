/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/11 17:06:07 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstnew(char *env)
{
	t_env			*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_substr(env, 0, ft_strchri(env, '='));
	if (!new_env->key)
		return (NULL);
	new_env->value = ft_substr(env, ft_strchri(env, '=') + 1, ft_strlen(env)
			- (ft_strchri(env, '=') + 1));
	if (!new_env->value)
		return (NULL);
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
	int		i;

	i = 0;
	new = NULL;
	new_node = NULL;
	while (envp[i] && envp)
	{
		new_node = lstnew(envp[i]);
		if (!new_node)
			return (NULL);
		lst_addback(&new, new_node);
		i++;
	}
	return (new);
}

char	**env_to_tab(t_data *data)
{
	t_env	*copy;
	char	**tab;
	int		i;

	tab = NULL;
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

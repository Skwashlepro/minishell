/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:55 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/30 20:38:19 by tpassin          ###   ########.fr       */
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
}

char	**env_to_tab(t_data *data)
{
	t_env	*cp;
	char	**tab;
	int		i;

	i = lst_size(data->get_env);
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	cp = data->get_env;
	while (cp)
	{
		tab[i] = ft_strjoin(cp->key, "=");
		tab[i] = ft_strjoin(tab[i], cp->value);
		i++;
		cp = cp->next;
	}
	tab[i] = NULL;
	return (tab);
}
// tab = ["USER=mgamil"] lst = key = "USER" value = "mgamil" next
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:28:17 by luctan            #+#    #+#             */
/*   Updated: 2024/10/16 22:04:32 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	known_key(char *args, t_data *data, int *i)
{
	t_env	*env;
	int		k;

	k = 0;
	env = data->get_env;
	while (args[k] && args[k] != '=')
		k++;
	while (env && ft_strncmp(env->key, args, ft_strlen(env->key)))
		env = env->next;
	if (env && !ft_strncmp(env->key, args, (size_t)k))
	{
		if (args[k] == '=')
		{
			free_array(env->value);
			env->equal = 1;
			env->value = ft_strdup(args + (++k));
			(*i)++;
			return (0);
		}
	}
	return (1);
}

t_env	*key_init(char *arg, int *index)
{
	t_env	*node;
	int		i;
	int		j;

	node = malloc(sizeof(t_env));
	i = 0;
	j = -1;
	while (arg[i] != '=' && arg[i])
		i++;
	*index = i;
	node->key = malloc(sizeof(char) * (i + 1));
	while (++j != i)
		node->key[j] = arg[j];
	node->key[j] = '\0';
	return (node);
}

void	print_exp(t_data *data)
{
	t_env	*tmp;

	tmp = data->get_env;
	while (tmp)
	{
		write(1, "export ", 8);
		write(1, tmp->key, ft_strlen(tmp->key));
		if (tmp->equal)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

int	exp_check(t_env **node, t_data *data)
{
	t_env	*tmp;

	if (!(*node))
		return (1);
	tmp = data->get_env;
	while (ft_strcmp(tmp->key, (*node)->key) && tmp->next)
		tmp = tmp->next;
	if (!ft_strcmp(tmp->key, (*node)->key))
		return (free_array((*node)->key), free((*node)), 1);
	(*node)->value = ft_strdup("");
	(*node)->equal = 0;
	(*node)->next = NULL;
	return (0);
}

int	export(t_data *data, char **args)
{
	int		i;
	int		j;
	t_env	*node;

	i = 0;
	j = 0;
	if (!args[1] || !data->get_env)
		return (print_exp(data), 0);
	node = NULL;
	while (args[++i])
	{
		if (!valid_id(&data, args[i]))
			continue ;
		if (known_key(args[i], data, &i))
			node = key_init(args[i], &j);
		if (args[i] && args[i][j])
			value_paste(node, args[i], ++j);
		else if (exp_check(&node, data))
			return (0);
		lst_addback(&data->get_env, node);
	}
	return (0);
}

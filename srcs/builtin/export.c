/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:28:17 by luctan            #+#    #+#             */
/*   Updated: 2024/10/08 17:37:38 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *key_init(char *arg, int *index)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (arg[i] != '=' && arg[i])
		i++;
	*index = i;
	tmp = malloc(sizeof(char) * (i + 1));
	while (++j != i)
		tmp[j] = arg[j];
	tmp[j] = '\0';
	printf("tmp is : %s\n", tmp);
	return (tmp);
}

void	print_exp(t_data *data)
{
	t_env	*tmp;

	tmp = data->get_env;
	while (tmp)
	{
		printf("export ");
		printf("%s=", tmp->key);
		printf("%c%s%c\n", '"', tmp->value, '"');
		tmp = tmp->next;
	}
}
int	export(t_data *data, char **args)
{
	int		i;
	int		j;
	t_env	*tmp;
	t_env	*node;

	i = 0;
	j = 0;
	if (!args[1])
		return (print_exp(data), 1);
	tmp = data->get_env;
	node = malloc(sizeof(t_env));
	while (args[++i])
	{
		node->key = key_init(args[i], &j);
		if (args[i][j])
		{
			node->value = ft_strdup(args[i] + (++j));
			node->equal = 1;
			node->next = NULL;
		}
		else if (node->key)
			while (tmp->key != node->key && tmp)
				tmp = tmp->next;
		lst_addback(&data->get_env, node);
	}
	return (0);
}

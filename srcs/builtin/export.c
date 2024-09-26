/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:28:17 by luctan            #+#    #+#             */
/*   Updated: 2024/09/26 15:53:08 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *key_init(char *arg, int *index)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	index = i;
	tmp = malloc(sizeof(char) * i);
	while (j != i)
		tmp[j] = arg[j++];
	tmp[j + 1] = '\0';
	return (tmp);
}

void	print_exp(t_data *data)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = data->get_env;
	while (tmp)
	{
		printf("export ");
		printf("%s=", tmp->key);
		printf("%c%s%c\n", '"',tmp->value, '"');
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
	tmp = data->get_env;
	if (!args)
		return (print_exp(data), 1);
	while (args[i])
	{
		node->key = key_init(args[i], &j);
		if (args[i][j])
		{
			j++;
			node->value = ft_strdup(args[i] + j);
			node->equal = 1;
		}
		else if (node->key)
		{
			while (tmp->key != node->key && tmp)
				tmp = tmp->next;
		}
		lst_addback(data->get_env, node);
		i++;
	}
}

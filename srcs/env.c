/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:33:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/12 18:03:47 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->cquote = 'N';
}

void	print_env(t_data *data)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = data->get_env;
	while (tmp)
	{
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

t_env	*init_env(char **envp, int ac)
{
	int	i;

	if (ac != 1)
	{
		ft_putstr_fd("Error too many args\n", 2);
		exit(1);
	}
	i = 0;
	ft_signal();
	return (copy_env(envp));
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

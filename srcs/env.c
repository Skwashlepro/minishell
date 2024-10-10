/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:33:02 by luctan            #+#    #+#             */
/*   Updated: 2024/10/11 00:04:27 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->cquote = 'N';
}

t_env	*init_env(char **envp, int ac)
{
	if (ac != 1)
	{
		ft_putstr_fd("Error too many args\n", 2);
		exit(1);
	}
	ft_signal();
	return (copy_env(envp));
}

char	**env_to_tab(t_data *data)
{
	t_env	*copy;
	char	**tab;
	char	*str;
	int		i;

	tab = NULL;
	str = NULL;
	i = lst_size(data->get_env);
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	copy = data->get_env;
	i = 0;
	while (copy && tab)
	{
		str = ft_strjoin(copy->key, "=");
		if (!str)
		{
			if (tab)
				free_tab(tab);
			return (NULL);
		}
		tab[i] = ft_strjoin(str, copy->value);
		if (!tab[i])
			return (free(str), NULL);
		free(str);
		copy = copy->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

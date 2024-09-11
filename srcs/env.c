/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:33:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/11 17:18:04 by tpassin          ###   ########.fr       */
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
	t_env *tmp;
	int	i;

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
		exit (1);
	}
	i = 0;
	ft_signal();
	// while (envp[i])
	// 	i++;
	// data->env = (char **)malloc(sizeof(char *) * (i + 1));
	// if (!data->env)
	// 	return (exit(1));
	// i = -1;
	// while (envp && envp[++i])
	// 	data->env[i] = ft_strdup(envp[i]);
	// data->env[i] = 0;
	return (copy_env(envp));
}

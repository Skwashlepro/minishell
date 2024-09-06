/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:33:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/06 20:07:15 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->prompt = NULL;
	data->head = NULL;
	data->get_env = NULL;
	data->cquote = 'N';
}

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

void	init_env(t_data *data, char **envp, int ac)
{
	int	i;

	ft_signal();
	if (ac != 1)
	{
		ft_putstr_fd("Error too many args\n", 2);
		return (exit(1));
	}
	i = 0;
	while (envp[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (exit(1));
	i = -1;
	while (envp && envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = 0;
	copy_env(data);
}

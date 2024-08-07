/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:33:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/07 19:16:24 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

void init_env(t_data *data, char **envp, int ac)
{
    if (ac != 1)
    {
        ft_putstr_fd("Error too many args\n", 2);
        exit (1);
    }
    int i;

    i = 0;
    while (envp[i])
		i++;
	data->env = malloc(sizeof(char **) * i + 1);
	if (!data->env)
		exit (1);
	i = -1;
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = 0;
}
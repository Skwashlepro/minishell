/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:47:54 by luctan            #+#    #+#             */
/*   Updated: 2024/10/11 05:19:26 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_data *data)
{
	t_env *env;

	env = data->get_env;
	while (env)
	{
		ft_printf(1, "%s%c%s\n", env->key, '=', env->value);
		env = env->next;
	}
	return ;
}
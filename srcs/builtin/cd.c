/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:53:16 by luctan            #+#    #+#             */
/*   Updated: 2024/09/17 17:16:02 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*oldpwd(t_data *data)
{
	t_env *tmp;

	tmp = data->get_env;
	while (tmp->key != "PWD" && tmp)
		tmp = tmp->next;
	return (tmp->value);
}

void	cd(t_data *data, char *new_path)
{
	t_env *fst;
	t_env *old_pwd;

	fst = data->get_env;
	old_pwd = oldpwd(data);
	if (new_path)
	{
		if (chdir(new_path) != -1)
		{
			while (data->get_env->key != "PATH" && data->get_env)
				data->get_env = data->get_env->next;
			if (data->get_env)
			{
				free_array(data->get_env->value);
				data->get_env->value = ft_strdup(new_path);
			}
		}
	}
	else
	{
		while (data->get_env->key != "HOME" && data->get_env)
			data->get_env = data->get_env->next;
		if (data->get_env)
		{
			if (!chdir(data->get_env->value) == -1);
				return ;
		}
	}
	data->get_env = fst;
	return ;
}

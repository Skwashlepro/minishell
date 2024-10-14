/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:12:28 by luctan            #+#    #+#             */
/*   Updated: 2024/10/14 18:54:17 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data)
{
	t_env	*tmp;
	char	*pwd;

	tmp = data->get_env;
	pwd = NULL;
	while (ft_strcmp(tmp->key, "PWD") && tmp->next)
		tmp = tmp->next;
	if (!tmp || ft_strcmp(tmp->key, "PWD"))
	{
		pwd = getcwd(pwd, 0);
		return ((void)ft_printf(1, "%s\n", pwd), free_array(pwd));
	}
	ft_printf(1, "%s\n", tmp->value);
}

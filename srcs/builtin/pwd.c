/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:12:28 by luctan            #+#    #+#             */
/*   Updated: 2024/10/08 19:40:28 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data)
{
	t_env *tmp;
	char	*PWD;

	tmp = data->get_env;
	PWD = NULL;
	while (ft_strcmp(tmp->key, "PWD") && tmp->next)
		tmp = tmp->next;
	if (ft_strcmp(tmp->key, "PWD"))
	{
		PWD = getcwd(PWD, 0);
		return((void)printf("%s\n", PWD));
	}
	printf("%s\n", tmp->value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:12:28 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 19:58:26 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data)
{
	t_env	*tmp;
	int		i;
	char	*pwd;

	i = 0;
	tmp = data->get_env;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	while (pwd[i])
		write(1, &pwd[i++], 1);
	write(1, "\n", 1);
	free_array(pwd);
}

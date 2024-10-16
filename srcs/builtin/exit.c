/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:01:11 by luctan            #+#    #+#             */
/*   Updated: 2024/10/16 22:29:04 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(t_data *data, char **args, char **envp, int nb)
{
	(void)args;
	free_exec(envp, data->path);
	free_env(data->get_env);
	ft_clean(data);
	exit(nb);
}

void	ft_exit(char **args, t_data *data, char **envp)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	ft_printf(1, "exit\n");
	while (args[i])
		i++;
	if (i == 1)
		return (exit_free(data, args, envp, 0));
	if (i > 2)
	{
		data->exit_status = 1;
		return ((void) !ft_printf(2, "minishell: exit: too many arguments\n"));
	}
	if ((i == 2 && !nb_check(args[1])))
		return (ft_printf(2, "minishell: exit: %s: numeric argument required\n",
				args[1]), exit_free(data, args, envp, 2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
	}
	return (exit_free(data, args, envp, nb));
}

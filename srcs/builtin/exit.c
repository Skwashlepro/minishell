/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:01:11 by luctan            #+#    #+#             */
/*   Updated: 2024/10/15 15:39:40 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(t_data *data, char **args, int nb)
{
	(void)args;
	free_env(data->get_env);
	ft_clean(data);
	exit(nb);
}

void	ft_exit(char **args, t_data *data)
{
	int		i;
	long	nb;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		return (exit_free(data, args, 0));
	if (i > 2)
		return ((void) !ft_printf(2, "minishell: exit: too many arguments\n"));
	if ((i == 2 && !nb_check(args[1])))
		return (ft_printf(2, "minishell: exit: %s: numeric argument required\n",
				args[1]), exit_free(data, args, 2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
		return (exit_free(data, args, nb));
	}
	else
		return (exit_free(data, args, 0));
}

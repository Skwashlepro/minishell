/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:01:11 by luctan            #+#    #+#             */
/*   Updated: 2024/10/14 18:54:28 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, t_data *data)
{
	int		i;
	long	nb;

	i = 0;
	(void)data;
	while (args[i])
		i++;
	if (i == 1)
		return (exit(0));
	if (i > 2)
		return ((void) !ft_printf(2, "minishell: exit: too many arguments\n"));
	if ((i == 2 && !nb_check(args[1])))
		return (ft_printf(2, "minishell: exit: %s: numeric argument required\n",
				args[1]), free_tab(args), exit(2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
		free_tab(args);
		return (exit(nb));
	}
	else
		return (exit(0));
}

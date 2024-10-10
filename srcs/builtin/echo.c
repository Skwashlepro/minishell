/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:52:28 by luctan            #+#    #+#             */
/*   Updated: 2024/10/08 21:07:54 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dash_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (!str[i])
			return (0);
	}
	return (1);
}

void	echo(char **args)
{
	int print;
	int i;

	print = 0;
	i = 1;
	while (args[i] && !dash_n(args[i++]))
		print = 1;
	while (args[i])
	{
		ft_printf(1, "%s", args[i++]);
		if (args[i])
			ft_printf(1, " ");
	}
	if (!print)
		ft_printf(1, "\n");
}
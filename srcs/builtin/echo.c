/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:52:28 by luctan            #+#    #+#             */
/*   Updated: 2024/10/02 20:09:14 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	print;
	int	i;

	print = 0;
	i = 0;
	if (!ft_strcmp(args[i], "-n"))
	{
		print = 1;
		i++;
	}
	while (args[i])
		printf("%s ", args[i++]);
	if (!print)
		printf("\n");
}
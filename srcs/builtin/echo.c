/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:52:28 by luctan            #+#    #+#             */
/*   Updated: 2024/10/03 19:47:37 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	print;
	int	i;

	print = 0;
	i = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		print = 1;
		i++;
	}
	printf("%i\n", print);
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!print)
		printf("\n");
}
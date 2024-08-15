/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 03:51:40 by luctan            #+#    #+#             */
/*   Updated: 2024/08/15 19:11:47 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	nb_error(char **args)
{
	printf("minishell: exit: %s: numeric argument required\n", args[1]);
	free_tab(args);
	exit(2);
}

long	ft_atol(char **nb)
{
	long	n;
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	n = 0;
	while (nb[1][i] == 32 || (nb[1][i] >= 9 && nb[1][i] <= 13))
		i++;
	if (nb[1][i] == '+' || nb[1][i] == '-')
	{
		if (nb[1][i] == '-')
			sign = -1;
		i++;
	}
	while (nb[1][i] && nb[1][i] >= '0' && nb[1][i] <= '9')
	{
		if (n > (LONG_MAX - (nb[1][i] - '0')) / 10)
			nb_error(nb);
		n = n * 10 + (nb[1][i++] - '0');
	}
	return (n * sign);
}

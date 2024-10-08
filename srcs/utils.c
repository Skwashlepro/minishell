/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 03:51:40 by luctan            #+#    #+#             */
/*   Updated: 2024/10/08 16:19:29 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_array(char *str)
{
	free(str);
	str = NULL;
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

int	redirection_input(char *s, int in, int out)
{
	if (((ft_strchr("<>", *s)) && (in || out)))
	{
		if (*(s - 1) && is_space(*(s - 1)))
			return (1);
	}
	if (*s == '|' && ((out || in)))
		return (1);
	return (0);
}

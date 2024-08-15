/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 03:51:40 by luctan            #+#    #+#             */
/*   Updated: 2024/08/15 18:15:04 by luctan           ###   ########.fr       */
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

long long	ft_atol(const char *nb)
{
	long	n;
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	n = 0;
	while (nb[i] == ' ' || nb[i] == '\t' || nb[i] == '\n' || nb[i] == '\r'
		|| nb[i] == '\f' || nb[i] == '\v')
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			sign = -1;
		i++;
	}
	while (nb[i] && ft_isdigit(nb[i]))
	{
		n = n * 10 + (nb[i++] - 48);
	}
	return (n * sign);
}
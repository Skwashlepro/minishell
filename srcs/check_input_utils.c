/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:47:15 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/22 17:22:29 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_check(char *str)
{
	int	error;
	int	i;

	i = 0;
	error = 1;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			error = 0;
			break ;
		}
		i++;
	}
	return (error);
}

void	ft_exit(char *str)
{
	char	**args;
	int		i;
	long	nb;

	i = 0;
	if (i > 2)
		return ((void) !printf("minishell: exit: too many arguments\n"));
	args = ft_split(str, ' ');
	while (args[i])
		i++;
	if ((i == 2 && !nb_check(args[1])))
		return (printf("minishell: exit: %s: numeric argument required\n",
				args[1]), free_tab(args), exit(2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
		free_tab(args);
		return (printf("exit\n"), exit((int)nb));
	}
	else
		return (free_tab(args), printf("exit\n"), exit(0));
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	inquotes(char c, int i)
{
	int dq;
	int sq;

	dq = 0;
	sq = 0;
	if (c == '"' && !i && !sq)
	{
		i = 1;
		dq = 1;
	}
	else if (c == '"' && i && !sq)
	{
		i = 0;
		dq = 0;
	}
	return (i);
}

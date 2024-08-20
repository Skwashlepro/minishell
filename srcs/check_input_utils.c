/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:47:15 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/20 23:36:40 by tpassin          ###   ########.fr       */
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
	args = ft_split(str, ' ');
	while (args[i])
		i++;
	if (i > 2)
		return ((void) !printf("%s\n", "minishell: exit: too many arguments"));
	else if ((i == 2 && !nb_check(args[1])))
		return ((void) !printf("%s%s: %s\n", "minishell: exit: ",
				args[1], "numeric argument required"), exit(2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
		free_tab(args);
		return (printf("exit\n"), exit((int)nb));
	}
	else
		return (printf("exit\n"), exit(0));
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	inquotes(char c, int i)
{
	if ((c == '"' || c == '\'') && !i)
		i = 1;
	else if ((c == '"' || c == '\'') && i)
		i = 0;
	return (i);
}

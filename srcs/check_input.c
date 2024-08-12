/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:37 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/12 20:27:07 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_quotes(char *str)
{
	char	quote;

	quote = 'N';
	while (*str)
	{
		if (*str == '\'' && quote == 'N')
			quote = '\'';
		else if (*str == '\"' && quote == 'N')
			quote = '\"';
		else if (*str == '\'' && quote == '\'')
			quote = 'N';
		else if (*str == '\"' && quote == '\"')
			quote = 'N';
		str++;
	}
	return (quote);
}

static int	special_char(char c, int i)
{
	if (ft_strchr("|&()", c) && i == 0)
		return (1);
	else if (ft_strchr("|&()", c) && i == 1)
		return (0);
	else
		return (1);
}

int	check2(char *str, int i, bool pipe)
{
	while (*str)
	{
		i = (inquotes(*str, i));
		if (special_char(*str, i))
		{
			if (ft_strchr("|", *str) && !pipe)
				pipe = true;
			else if (ft_strchr("()&", *str))
				return (1);
			else if (*str == '|' && *(str + 1) == '|')
				return (1);
			else if (check_space(*str))
				str++;
			else if (ft_isalpha(*str) && pipe)
				pipe = false;
			else
				str++;
		}
		else
			str++;
	}
	if (pipe || i == 1)
		return (1);
	return (0);
}

int	check_char(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = false;
	while (*str && check_space(*str))
		str++;
	if (ft_strchr("|()&", *str))
		return (1);
	return (check2(str, i, pipe));
}

int	check_input(char *str)
{
	if (check_quotes(str) != 'N')
		return (printf("Error\n"), 1);
	if (check_char(str))
		return (ft_putstr_fd("Error\n", 2), 1);
	return (0);
}

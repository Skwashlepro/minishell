/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:37 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/14 03:11:15 by luctan           ###   ########.fr       */
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
			quote = '"';
		else if (*str == '\'' && quote == '\'')
			quote = 'N';
		else if (*str == '"' && quote == '"')
			quote = 'N';
		str++;
	}
	return (quote);
}

static int	special_char(char c, int i)
{
	if (ft_strchr("|&()", c) && !i)
		return (1);
	else if (ft_strchr("|&()", c) && i)
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
			else if (ft_isalpha(*str) && pipe)
				pipe = false;
			else if (*str == '|' && pipe)
				return (1);
			str++;
		}
		else
			str++;
	}
	return (pipe || i);
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

int	check_input(char *str, t_data *data)
{
	if (ft_strncmp(str, "exit\n", 4) == 0)
		ft_exit(str);
	if (ft_strnstr(str, "pwd", 3))
		printf("%s\n", getenv("PWD"));
	if (ft_strncmp(str, "env", 3) == 0)
		print_env(data);
	if (check_quotes(str) != 'N')
		return (printf("syntax error unclosed quotes\n"), 1);
	if (check_char(str))
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n",
				2), 1);
	return (0);
}

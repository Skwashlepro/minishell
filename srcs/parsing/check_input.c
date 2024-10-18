/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:37 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/09 15:52:46 by tpassin          ###   ########.fr       */
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
		return (0);
	else if (i)
		return (1);
	else
		return (0);
}

int	check_metachar(char *str)
{
	int		i;
	bool	pipe;

	i = 0;
	pipe = false;
	if (*str && ft_strchr("|()&", *str))
		return (1);
	while (*str)
	{
		i = (inquotes(*str, i));
		if (!special_char(*str, i))
		{
			if (ft_strchr("|", *str) && !pipe)
				pipe = true;
			else if (ft_strchr("()&", *str) || (*str == '|' && pipe))
				return (1);
			else if (!is_space(*str) && pipe)
				pipe = false;
			str++;
		}
		else
			str++;
	}
	return (pipe);
}

int	check_redir(char *s)
{
	int	in;
	int	out;
	int	i;

	in = 0;
	out = 0;
	i = 0;
	while (*s)
	{
		if (!inquotes(*s, i) && *s)
		{
			if (redirection_input(s, in, out))
				return (1);
			char_redir(s, &out, &in);
		}
		else
		{
			if (in && !is_space(*s) && in <= 2 && !out)
				in = 0;
			else if (out && !is_space(*s) && out <= 2 && !in)
				out = 0;
		}
		s++;
	}
	return (in || out);
}

int	check_input(char *str)
{
	while (*str && is_space(*str))
		str++;
	if (check_quotes(str) != 'N')
		return (ft_putstr_fd("syntax error unclosed quotes\n", 2), 1);
	if (check_metachar(str) || check_redir(str))
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n",
				2), 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:37 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/24 14:18:01 by tpassin          ###   ########.fr       */
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
			else if (ft_isalnum(*str) && pipe)
				pipe = false;
			str++;
		}
		else
			str++;
	}
	return (pipe);
}

int	check_redir(char *str)
{
	int	redir;
	int	redir_out;
	int	i;

	redir = 0;
	redir_out = 0;
	i = 0;
	while (*str)
	{
		if (!inquotes(*str, i))
		{
			if(((*str == '<' || *str) && is_space(*(str - 1)) && (redir || redir_out)))
				return (1);
			char_redir(str, &redir_out, &redir);
		}
		else
		{
			if (redir && !is_space(*str) && redir <= 2 && !redir_out)
				redir = 0;
			else if (redir_out && !is_space(*str) && redir_out <= 2 && !redir)
				redir_out = 0;
		}
		str++;
	}
	return (redir || redir_out);
}

int	check_input(char *str, t_data *data)
{
	while (*str && is_space(*str))
		str++;
	if (check_quotes(str) != 'N')
		return (ft_putstr_fd("syntax error unclosed quotes\n", 2), 1);
	if (check_metachar(str) || check_redir(str))
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n",
				2), 1);
	if (ft_strncmp(str, "exit\n", 4) == 0)
		ft_exit(str);
	if (ft_strnstr(str, "pwd", 3))
		printf("%s\n", getenv("PWD"));
	if (ft_strncmp(str, "env", 3) == 0)
		print_env(data);
	return (0);
}

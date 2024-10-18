/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:47:15 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/18 16:00:12 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_check(char *str)
{
	int	error;
	int	i;

	i = 0;
	error = 1;
	if (str[0] == '-' || str[0] == '+')
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

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	inquotes(char c, int i)
{
	static int	dq = 0;
	static int	sq = 0;

	if (c == '"' && !sq)
		dq = !dq;
	else if (c == '\'' && !dq)
		sq = !sq;
	i = (dq || sq);
	return (i);
}

void	char_redir(char *str, int *redir_out, int *redir)
{
	if (*str == '<')
		(*redir)++;
	if (*str == '>')
		(*redir_out)++;
	if ((*str != '<' && *str != '>' && !is_space(*str)) && *redir <= 2
		&& !(*redir_out))
		*redir = 0;
	if ((*str != '<' && *str != '>' && !is_space(*str)) && *redir_out <= 2
		&& !(*redir))
		*redir_out = 0;
}

int	only_quote(char *s)
{
	int	i;

	i = 0;
	while (is_space(s[i]))
		i++;
	if (s[i])
	{
		while (s[i] == '"' || s[i] == '\'')
			i++;
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:47:15 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/17 16:06:47 by luctan           ###   ########.fr       */
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
	else if (*str == '>')
		(*redir_out)++;
	else if (ft_isalnum(*str) && *redir <= 2 && !(*redir_out))
		*redir = 0;
	else if (ft_isalnum(*str) && *redir_out <= 2 && !(*redir))
		*redir_out = 0;
}

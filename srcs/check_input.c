/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:37 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/08 19:18:16 by tpassin          ###   ########.fr       */
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

// static int check_all(char *str)
// {
// 	bool 	quote;
// 	int		sq;

// 	sq = 0;
// 	quote = false;
// 	while (*str)
// 	{
// 		if (*str == '\'' && !quote)
// 		{
// 			sq = 1;
// 			quote = true;
// 		}
// 		else if (*str == '\"' && !quote && !sq)
// 			quote = true;
// 		else if (*str == '\'' && sq)
// 			quote = false;
// 		else if (*str == '\"' && quote)
// 			quote = false;
// 		else if (quote && *str != '\"')
// 		{
// 			if (ft_strchr("&|;", *str))
// 				str++;
// 		}
// 		else if (sq && quote && *str != '\'')
// 		{
// 			if (ft_strchr("&|;", *str))
// 				str++;	
// 		}
// 		else if (!quote && ft_strchr("&|';", *str))
// 				return (1);
// 	}
// 	return (quote);
// }

int	check_input(char *str)
{
	if (check_quotes(str) != 'N')
		return (printf("Error\n"), 1);
	if (check_all(str))
		return (ft_putstr_fd("Error\n", 2), 1);
	return (0);
}
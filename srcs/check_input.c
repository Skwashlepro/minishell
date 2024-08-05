/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:37 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/05 21:06:54 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// int	logical_operator(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == '&' && *(str + 1) == '&')
// 			return (1);
// 		if (*str == '&' && *(str + 1) != '&')
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

char	check_quotes(char *str)
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

int	check_input(char *str)
{
	if (check_quotes(str) != 'N')
		return (printf("Error\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac;
	if (check_input(av[1]))
		return (1);
}
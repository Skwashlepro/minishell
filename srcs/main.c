/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/06 17:19:09 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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


void	INThandler(int sig)
{
	signal(sig, SIG_IGN);
	printf("CTRL + C detected");
}

char	*prompter(void)
{
	char *input;

	input = NULL;
	signal(SIGINT, INThandler);
	input = readline("$minishell ");
	return (input);
}

int	parsing(char *prompt)
{
	if (prompt)
		return (1);
	return (0);
}

int	main()
{
	char *prompt;
	
	while (1)
	{
		prompt = prompter();
		printf("%s\n", prompt);
		if (ft_strncmp(prompt, "exit", 4) == 0)
			break ;
		check_input(prompt);
		free(prompt);
	}
	free(prompt);
	return (0);	
}
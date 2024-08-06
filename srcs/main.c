/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/06 18:03:53 by luctan           ###   ########.fr       */
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
	(void)sig;
	write (1, "\n", 1);
	rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
	return ;
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
	t_data data;
	
	while (1)
	{
		data.prompt = prompter();
		// printf("%s\n", data.prompt);
		if (ft_strncmp(data.prompt, "exit", 4) == 0)
			break ;
		if (ft_strnstr(data.prompt, "pwd", 3))
			printf("%s\n", getenv("PWD"));
		check_input(data.prompt);
		free(data.prompt);
	}
	free(data.prompt);
	return (0);	
}
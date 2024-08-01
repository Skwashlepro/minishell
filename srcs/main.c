/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/01 14:40:58 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (1)
	{
		input = readline("$minishell");
		if (input)
			break ;
	}
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

	prompt = prompter();
	if (parsing(prompt))
		printf("%s\n", prompt);	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/13 16:36:27 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

char	*prompter(void)
{
	char	*input;

	input = NULL;
	input = readline("minishell$ ");
	return (input);
}

int	main(int ac, char **av, char **envp)
{
	t_data data = {0};
	(void)av;
	init_env(&data, envp, ac);
	while (1)
	{
		ft_signal();
		data.prompt = prompter();
		if (data.prompt == NULL)
			break ;
		if (ft_strncmp(data.prompt, "exit\n", 4) == 0)
			break ;
		if (ft_strnstr(data.prompt, "pwd", 3))
			printf("%s\n", getenv("PWD"));
		if (ft_strncmp(data.prompt, "env", 3) == 0)
			print_env(&data);
		if (!check_input(data.prompt))
			printf("%s\n", data.prompt);
		free(data.prompt);
	}
	free(data.prompt);
	return (0);
}
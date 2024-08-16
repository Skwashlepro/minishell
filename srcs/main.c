/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/16 18:02:58 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

char	*prompter(void)
{
	char	*input;

	input = readline("minishell$ ");
	return (input);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	init_env(&data, envp, ac);
	while (1)
	{
		ft_signal();
		data.prompt = prompter();
		if (data.prompt == NULL)
			break ;
		if (!check_input(data.prompt, &data) && *data.prompt)
		{
			printf("%s\n", data.prompt);
			add_history(data.prompt);
		}
		free(data.prompt);
	}
	free(data.prompt);
	return (0);
}

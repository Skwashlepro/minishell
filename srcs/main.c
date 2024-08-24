/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/24 10:58:06 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

char	*prompter(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
		return (NULL);
	if (*input)
	{
		printf("%s\n", input);
		add_history(input);
	}
	return (input);
}

void	loop_prog(t_data *data)
{
	while (1)
	{
		data->prompt = prompter();
		if (!data->prompt)
			break ;
		tokenizer(data, data->prompt);
		while (data->head)
		{
			printf("string: %s\ntype: %u\n", data->head->str, data->head->type);
			printf("\n----------------------------------------\n");
			data->head = data->head->next;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	init_data(&data);
	init_env(&data, envp, ac);
	loop_prog(&data);
	return (0);
}

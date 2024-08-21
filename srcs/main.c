/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/08/21 19:47:03 by luctan           ###   ########.fr       */
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

void	loop_prog(t_data *data, t_token **head)
{
	while (1)
	{
		data->prompt = prompter();
		if (!data->prompt)
			break ;
		tokenizer(head, data, data->prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_token *head;

	(void)av;
	head = NULL;
	init_data(&data, head);
	init_env(&data, envp, ac);
	loop_prog(&data, &head);
	return (0);
}

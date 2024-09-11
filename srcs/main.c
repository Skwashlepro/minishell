/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/11 17:25:39 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

// void print_node(char *str, int type)
// {
// 	printf("\n----------------------------------------\n");
// 	printf("string: %s\n", str);
//     switch(type)
// 	{
//         case 0: printf("type: WORD\n"); break ;
//         case 1: printf("type: PIPE\n"); break ;
//         case 2: printf("type: REDIRECTION\n"); break ;
// 	}
// 	printf("----------------------------------------\n");
// }

void	clean_all(t_data *data)
{
		ft_clean(data);
		free_env(data->get_env);
		rl_clear_history();
		exit (1);
}

char	*prompter(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
		clean_all(data);
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
		data->prompt = prompter(data);
		tokenizer(data, data->prompt);
		// while (data->head)
		// {
		// 	print_node(data->head->str, data->head->type);
		// 	data->head = data->head->next;
		// }
		ft_clean(data);
		free(data->prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	init_data(&data);
	data.get_env = init_env(envp, ac);
	if (!data.get_env)
		return (clean_all(&data), 1);
	loop_prog(&data);
	clean_all(&data);
	// printf("exit\n");
	return (0);
}

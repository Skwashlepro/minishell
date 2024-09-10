/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/10 19:19:58 by luctan           ###   ########.fr       */
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

void	clean_env(t_data *data)
{
	if (data->get_env)
		free_env(data);
}

char	*prompter(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
		return (ft_clean(data), clean_env(data), exit(1), NULL);
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
		data->env = env_to_tab(data);
		free(data->prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	init_data(&data);
	init_env(&data, envp, ac);
	loop_prog(&data);
	ft_clean(&data);
	clean_env(&data);
	// printf("exit\n");
	return (0);
}

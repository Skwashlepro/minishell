/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/04 15:40:22 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

void print_node(char *str, int type)
{
	printf("\n----------------------------------------\n");
	printf("string: %s\n", str);
    switch(type)
	{
        case 0: printf("type: CMD\n"); break ;
        case 1: printf("type: ARG\n"); break ;
        case 2: printf("type: WORD\n"); break ;
        case 3: printf("type: PIPE\n"); break ;
        case 4: printf("type: INFILE\n"); break ;
        case 5: printf("type: OUFILE\n"); break ;
        case 6: printf("type: REDIR_IN\n"); break ;
        case 7: printf("type: REDIR_OUT\n"); break ;
        case 8: printf("type: HERE_DOC\n"); break ;
        case 9: printf("type: APPEND\n"); break ;
        case 10: printf("type: LIMITER\n"); break ;
        case 11: printf("type: ENV_VAR\n"); break ;
	}
	printf("----------------------------------------\n");
}

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
			print_node(data->head->str, data->head->type);
			data->head = data->head->next;
		}
		ft_clean(data);
		data->env = env_to_tab(data);
	}
}

void	clean_env(t_data *data)
{
	if (data->get_env)
		free_env(&data);
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
	return (0);
}

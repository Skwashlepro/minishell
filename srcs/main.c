/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/09/19 18:33:31 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

// void print_node(t_token *token, int type)
// {
// 	while (token)
// 	{
// 		printf("\n----------------------------------------\n");
// 		printf("string: %s\n", token->str);
// 		printf("nb_quotes: %d\n", token->nb_quotes);
//     	switch(type)
// 		{
//     		 case 0: printf("type: WORD\n"); break ;
//     		 case 1: printf("type: PIPE\n"); break ;
//     		 case 2: printf("type: REDIRECTION\n"); break ;
// 		}
// 		printf("----------------------------------------\n");
// 		token = token->next;
// 	}
// }

void	clean_all(t_data *data)
{
	clean_cmd(data->cmd);
	ft_clean(data);
	free_env(data->get_env);
	rl_clear_history();
	exit(1);
}

char	*prompter(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL || (*input == EOF))
		clean_all(data);
	if (ft_strchr("!#", input[0]) || input[0] == '\0')
		return (free(input), ft_strdup(""));
	if (*input)
	{
		// printf("%s\n", input);
		add_history(input);
	}
	return (input);
}

void	loop_prog(t_data *data)
{
	int	i;

	while (1)
	{
		data->prompt = prompter(data);
		data->head = tokenizer(data, data->prompt);
		data->cmd = parsing(data);
		if (data->cmd)
		{
			i = 0;
			while (data->cmd->arguments[i])
				printf("%s\n", data->cmd->arguments[i++]);
		}
		// print_node(data->head, data->head->type);
		ft_clean(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	init_data(&data);
	// char *s = malloc(sizeof(char *) * (1000));
	// s = ft_strdup("HELLO");
	data.get_env = init_env(envp, ac);
	if (!data.get_env)
		return (free_env(data.get_env), 1);
	loop_prog(&data);
	clean_all(&data);
	// printf("exit\n");
	return (0);
}

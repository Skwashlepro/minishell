/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:02 by luctan            #+#    #+#             */
/*   Updated: 2024/10/10 18:31:39 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var = 0;

// void	print_node(t_token *token, int type)
// {
// 	while (token)
// 	{
// 		printf("\n----------------------------------------\n");
// 		printf("string: %s\n", token->str);
// 		printf("nb_quotes: %d\n", token->nb_quotes);
// 		switch (type)
// 		{
// 		case 0:
// 			printf("type: WORD\n");
// 			break ;
// 		case 1:
// 			printf("type: PIPE\n");
// 			break ;
// 		case 2:
// 			printf("type: REDIRECTION\n");
// 			break ;
// 		}
// 		printf("----------------------------------------\n");
// 		token = token->next;
// 	}
// }

void	clean_all(t_data *data)
{
	int	quit;

	quit = 0;
	if (data->heredoc)
		quit = data->heredoc;
	ft_clean(data);
	free_env(data->get_env);
	// rl_clear_history();
	if (quit > 15)
		exit(2);
	exit(0);
}

char	*prompter(t_data *data)
{
	char	*input;

	(void)data;
	input = readline("minishell$ ");
	if (input == NULL)
		return (NULL);
	// if (*input)
	// 	add_history(input);
	return (input);
}

void	unlink_file(void)
{
	int		i;
	char	*tmp_itoa;
	char	*filename;

	i = 1;
	while (1)
	{
		tmp_itoa = ft_itoa(i);
		filename = ft_strjoin(GET_HEREDOC, tmp_itoa);
		if (access(filename, F_OK) == -1)
		{
			free(tmp_itoa);
			free(filename);
			break ;
		}
		unlink(filename);
		free(tmp_itoa);
		free(filename);
		i++;
	}
}

void	loop_prog(t_data *data)
{
	while (1)
	{
		data->prompt = prompter(data);
		if (!data->prompt)
			break ;
		if (g_var != 0)
		{
			data->exit_status = g_var;
			g_var = 0;
		}
		if (ft_strcmp("env", data->prompt) == 0)
			print_env(data);
		data->head = tokenizer(data, data->prompt);
		data->cmd = parsing(data);
		if (data->cmd)
			data->exit_status = ft_exec(data->cmd, data);
		ft_clean(data);
		unlink_file();
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	init_data(&data);
	data.get_env = init_env(envp, ac);
	if (!data.get_env)
		free_env(data.get_env);
	loop_prog(&data);
	clean_all(&data);
	return (0);
}

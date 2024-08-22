/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:15:48 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/22 20:12:32 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int worder(t_data *data, char *input, int pipe, int i)
{
	char *str;
	char **tab;
	int	j;

	j = 0;
	str = "";
	if (pipe)
	{
		while (input[pipe] != '>' && input[pipe] != '<' && input[pipe])
			str[j++] = input[pipe++];
		i = pipe;
	}
	else if (!pipe)
		while (input[i] != '|' && input[i] != '>' && input[i] != '<' && input[i])
			str[j++] = input[i++];
	str[j] = '\0';
	tab = ft_split(str, ' ');
	if (tab[0] && (input[i] != '|' && input[i] != '>' && input[i] != '<'))
		word_token(tab, data);
	return (i);
}

void	word_token(char **tab, t_data *data)
{
	int	k;
	int	i;
	int	index;
	char *str;

	i = -1;
	k = 0;
	index = 0;
	str = NULL;
	while (tab[++i])
	{
		while ((tab[i][k] != '"' || tab[i][k] != '\'') && tab[i][k])
			k++;
		str = ft_substr(tab[i], index, k);
		add_token(&data->head, WORD, str);
		index = k + 1;
		if (tab[i][k] == '\'')
			while (tab[i][k] != '\'' && tab[i][k])
				k++;
		else if (tab[i][k] == '"')
			while (tab[i][k] != '"' && tab[i][k])
				k++;
		str = ft_substr(tab[i], index, k - index);
		if (str[0])
			add_token(&data->head, WORD, str);
	}
}

void	isredirect(t_data *data, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[++*i] == '<')
		{
			add_token(&data->head, HERE_DOC, "<<");
			(*i)++;
		}
		else
			add_token(&data->head, REDIR_IN, "<");
	}
	else if (input[*i] == '>')
	{
		if (input[++*i] == '>')
		{
			add_token(&data->head, APPEND, ">>");
			(*i)++;
		}
		else
			add_token(&data->head, REDIR_OUT, ">");
	}
}

int	tokenizer(t_data *data, char *input)
{
	int	i;
	int	j;
	int pipe;

	i = 0;
	j = 0;
	pipe = 0;
	if (check_input(input, data))
		return(g_var = 2);
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			isredirect(data, input, &i);
		else if (input[i] == '|')
		{
			add_token(&data->head, PIPE, "|");
			pipe = i + 1;
		}
		i = worder(data, input, pipe, i);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:15:48 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/26 03:59:19 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int worder(t_data *data, char *input, int pipe, int i)
{
	char *str;
	char **tab;
	int	j;

	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (pipe)
	{
		while (input[pipe] != '|' && input[pipe] != '>' && input[pipe] != '<' && input[pipe])
			str[j++] = input[pipe++];
		i = pipe;
		pipe = 0;
	}
	else if (!pipe)
		while (input[i] != '|' && input[i] != '>' && input[i] != '<' && input[i])
			str[j++] = input[i++];
	str[j] = '\0';
	tab = ft_split(str, ' ');
	word_token(tab, data);
	return (i);
}

void	inquoteword(t_data *data, char **tab, int index, int *k)
{
	char *str;
	int	i;

	i = 0;
	str = NULL;
	if (tab[i][*k] == '\'' && tab[i][*k])
		while (tab[i][++*k] != '\'' && tab[i][*k])
			++*k;
	else if (tab[i][*k] == '"' && tab[i][*k])
		while (tab[i][++*k] != '"' && tab[i][*k])
			++*k;
		str = ft_substr(tab[i], index, *k - (index));
	add_token(&data->head, WORD, str);
}

void	word_token(char **tab, t_data *data)
{
	int		k;
	int		i;
	char	*str;
	int		index;

	i = -1;
	index = 0;
	str = NULL;
	while (tab[++i])
	{
		k = 0;
		while (tab[i][k])
		{
			index = k;
			if (tab[i][k] != '"' && tab[i][k] != '\'' && tab[i][k])
			{
				while ((tab[i][k] != '"' && tab[i][k] != '\'') && tab[i][k])
					k++;
				str = ft_substr(tab[i], index, k);
				add_token(&data->head, WORD, str);
				free_array(str);
			}
			else if ((tab[i][k] == '"' || tab[i][k] == '\'') && tab[i][k])
				inquoteword(data, (tab + i), index, &k);
		}
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
	int pipe;

	i = 0;
	pipe = 0;
	if (check_input(input, data))
		return (2);
	while (input[i])
	{
		pipe = 0;
		if (input[i] == '<' || input[i] == '>')
			isredirect(data, input, &i);
		else if (input[i] == '|')
		{
			add_token(&data->head, PIPE, "|");
			pipe = ++i;
		}
		i = worder(data, input, pipe, i);
	}
	return (0);
}

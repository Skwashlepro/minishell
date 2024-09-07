/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:15:48 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/07 20:32:23 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordinquote(char c, t_data *data)
{
	if (c == '"')
	{
		if (data->cquote == '\'')
			return (1);
		else if (data->cquote == 'N')
			data->cquote = c;
		else if (data->cquote == c)
			data->cquote = 'N';
		data->count++;
	}
	else if (c == '\'')
	{
		if (data->cquote == '"')
			return (1);
		else if (data->cquote == 'N')
			data->cquote = c;
		else if (data->cquote == c)
			data->cquote = 'N';
		data->count++;
	}
	if (data->cquote == 'N')
		return (0);
	return (1);
}

int	worder(t_data *data, char *str, int i)
{
	int		j;
	char	*new;

	j = i;
	new = NULL;
	if (str[i] == '\'' || str[i] == '"')
		i++;
	while (str[i])
	{
		wordinquote(str[i], data);
		if (data->cquote != 'N')
			i++;
		else if (is_sep(str[i]) && data->cquote == 'N')
			break ;
		else
			i++;
	}
	if (j != i)
	{
		new = ft_substr(str, j, i - j);
		add_token(&data->head, WORD, new);
		data->count = 0;
	}
	if (str[i] && is_space(str[i]) && data->cquote == 'N')
		i++;
	return (i);
}

void	isredirect(t_data *data, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[++(*i)] == '<')
		{
			add_token(&data->head, REDIRECTION, "<<");
			(*i)++;
		}
		else
			add_token(&data->head, REDIRECTION, "<");
	}
	else if (input[*i] == '>')
	{
		if (input[++(*i)] == '>')
		{
			add_token(&data->head, REDIRECTION, ">>");
			(*i)++;
		}
		else
			add_token(&data->head, REDIRECTION, ">");
	}
}

int	tokenizer(t_data *data, char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (check_input(input, data))
		return (2);
	while (input[i])
	{
		quote = wordinquote(input[i], data);
		if (ft_strchr("<|>", input[i]) && !quote)
		{
			if (input[i] == '<' || input[i] == '>')
				isredirect(data, input, &i);
			else if (input[i] == '|')
			{
				add_token(&data->head, PIPE, "|");
				++i;
			}
		}
		else
			i = worder(data, input, i);
	}
	return (0);
}

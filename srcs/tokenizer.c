/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:15:48 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/22 16:26:10 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int worder(t_token **head, char *input, int pipe, int i)
{
	char *str;
	char **tab;
	int	j;

	j = 0;
	str = NULL;
	if (pipe)
	{
		while (input[pipe] != '>' && input[pipe])
			str[j++] = input[pipe++];
		str[j] = '\0';
		i = pipe;
	}
	else if (!pipe)
	{
		while (input[i] != '|' && input[i])
			str[j++] = input[i++];
		str[j] = '\0';
	}
	if (str)
	{
		tab = ft_split(str, ' ');
		word_token(tab, head);
	}
	return (i);
}

void	word_token(char **tab, t_token **head)
{
	int	k;
	int	i;
	int	inq;
	int	index;
	char *str;
	
	i = -1;
	k = 0;
	inq = 0;
	index = 0;
	str = NULL;
	while (tab[++i])
	{
		while (tab[i][k] != '"' || tab[i][k] != '\'')
			k++;
		str = ft_substr(tab[i], index, k);
		if (str)
			add_token(head, WORD, str);
		str = NULL;
		if (tab[i][k] == '\'')
		{
			index = k + 1;
			while (tab[i][k] != '\'')
				k++;
		}
		else if (tab[i][k] == '"')
		{
			index = k + 1;
			while (tab[i][k] != '"')
				k++;
		}
		str = ft_substr(tab[i], index, k - index);
		if (str)
			add_token(head, WORD, str);
	}
}

void	isredirect(t_token **head, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[++*i] == '<')
			add_token(head, HERE_DOC, "<<");
		else
			add_token(head, REDIR_IN, "<");
	}
	else if (input[*i] == '>')
	{
		if (input[++*i] == '>')
			add_token(head, APPEND, ">>");
		else
			add_token(head, REDIR_OUT, ">");
	}	
}

int	tokenizer(t_token **head, t_data *data, char *input)
{
	int	i;
	int	j;
	int pipe;

	i = 0;
	j = 0;
	pipe = 0;
	if (check_input(input, data))
		return(g_var = 2, 2);
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			isredirect(head, input, &i);
		else if (input[i] == '|')
		{
			add_token(head, PIPE, "|");
			pipe = i + 1;
		}
		i = worder(head, input, pipe, i);
	}
	return (0);
}
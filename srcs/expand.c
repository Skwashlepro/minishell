/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:02:26 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/12 18:28:15 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote(t_data *data, char c, int *i)
{
	if (data->cquote == 'N')
	{
		data->cquote = c;
		(*i)++;
	}
	else
	{
		data->cquote = 'N';
		(*i)++;
	}
}

static int	wquote(char c, int *i, t_data *data)
{
	if (c == '"' && data->cquote != '\'')
	{
		update_quote(data, c, i);
		return (0);
	}
	else if (c == '\'' && data->cquote != '"')
	{
		update_quote(data, c, i);
		return (0);
	}
	return (1);
}

char	*get_varenv(t_data *data, char *str, int TYPE)
{
	int	i;
	int j;

	i = 0;
	if (TYPE == HERE_DOC)
		return (str);
	while (str[i])
	{
		j = 0;
		wordinquote(str[i], data);
		if (str[i] == '$' && data->cquote != '\'')
			while(str[i + j] != '$' && data->cquote != '"')
			{
				j++;
			}
			
	}
}

char	*ft_expand(t_data *data, char *str, int heredoc, int nb_quotes)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	str = get_varenv(str, data, heredoc);
	if (nb_quotes)
	{
		s = malloc(sizeof(char *) * ((ft_strlen(str) - data->count) + 1));
		if (!s)
			return (NULL);
		while (str[i])
		{
			if (wquote(str[i], &i, data))
				s[j++] = str[i++];
		}
		s[j] = '\0';
		return (s);
	}
	return (ft_strdup(str));
}

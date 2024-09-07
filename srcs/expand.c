/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:02:26 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/07 20:00:56 by tpassin          ###   ########.fr       */
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

char	*ft_expand(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	// printf("count: %d\n", data->count);
	if (data->count)
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

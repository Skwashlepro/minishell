/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:20:47 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/12 18:22:44 by tpassin          ###   ########.fr       */
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

int	wquote(char c, int *i, t_data *data)
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

void	process_string(char *str, t_data *data, int *pos, int *i)
{
	while (str && str[*i])
	{
		wordinquote(str[*i], data);
		if (str[*i] == '$' && str[*i + 1] && str[(*i) + 1] != '$'
			&& data->cquote != '\'' && !is_quotes(str[*i + 1]))
		{
			(*i)++;
			data->value = get_value(str, i, data);
			if (data->value)
			{
				data->new = ft_strncat(data->new, data->value,
						ft_strlen(data->value));
				*pos += ft_strlen(data->value);
				free_array(data->value);
			}
		}
		else if (data->cquote == 'N' && is_quotes(str[*i + 1]
				&& data->in_heredoc == 0) && str[*i] == '$')
			(*i)++;
		else
			(data->new)[(*pos)++] = str[(*i)++];
	}
}

void	loop_len(char *str, t_data *data, int *len, int *i)
{
	while (str && str[(*i)])
	{
		wordinquote(str[(*i)], data);
		if (str[(*i)] == '$' && str[(*i) + 1] && data->cquote != '\''
			&& str[(*i) + 1] != '$' && !is_quotes(str[(*i) + 1]))
		{
			(*i)++;
			data->new = get_value(str, i, data);
			if (data->new)
			{
				(*len) += ft_strlen(data->new);
				free_array(data->new);
			}
		}
		else if (data->cquote == 'N' && is_quotes(str[*i + 1]
				&& data->heredoc == 0) && str[*i] == '$')
			(*i)++;
		else
		{
			(*i)++;
			(*len)++;
		}
	}
}

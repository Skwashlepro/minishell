/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:02:26 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/17 18:03:35 by tpassin          ###   ########.fr       */
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

char	*get_value(char *str, int *i, t_data *data)
{
	int	j;

	j = 0;
	if (str[*i] == '$')
		return (NULL);
	if (str[*i] == '?')
		return ((*i += 1), ft_itoa(0));
	while (str[*i + j] && isalnum(str[*i + j]))
		j++;
	*i += j;
	while (data->get_env)
	{
		if (ft_strncmp(str + (*i - j), data->get_env->key, j) == 0)
			return (ft_strdup(data->get_env->value));
		data->get_env = data->get_env->next;
	}
	return (NULL);
}

int	len_varenv(t_data *data, char *str)
{
	int		len;
	int		i;
	char	*new;

	i = 0;
	len = 0;
	new = NULL;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			new = get_value(str, &i, data);
			if (new)
			{
				len += ft_strlen(new);
				free(new);
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

// char	*get_varenv(char *str, t_data *data, int TYPE)
// {
// 	int	i;
// 	int len;
// 	char *new;

// 	i = 0;
// 	if (TYPE == HERE_DOC && str)
// 		return (ft_strdup(str));
// 	len = len_varenv(data, str);
// 	new = malloc(sizeof(char *) * (len));
// 	if (!new)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		wordinquote(str[i], data);
// 		if (str[i] == '$' && data->cquote != '\'')
// 		{
// 			get->value
// 		}
// 	}
// 	return (NULL);
// }

char	*get_varenv(char *str, t_data *data, int TYPE)
{
	int		i;
	int		len;
	char	*new;
	char	*value;
	int		pos;

	i = 0;
	pos = 0;
	
	if (TYPE == HERE_DOC)
		return (ft_strdup(str));
	len = len_varenv(data, str);           
	new = calloc(sizeof(char), len + 1);
	value = NULL;
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		wordinquote(str[i], data);                              
		if (str[i] == '$' && str[i + 1] && data->cquote != '\'')
		{
			i++;
			value = get_value(str, &i, data);
			if (value)
			{
				new = strncat(new, value, ft_strlen(value));
				pos = ft_strlen(value);              
				free(value);
				value = 0;                         
			}
		}
		else
			new[pos++] = str[i++];
	}
	return (new);
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
		s = malloc(sizeof(char *) * ((ft_strlen(str) - nb_quotes) + 1));
		if (!s)
			return (NULL);
		while (str && str[i])
		{
			if (wquote(str[i], &i, data))
				s[j++] = str[i++];
		}
		s[j] = '\0';
		if (!s)
			return (NULL);
		return (s);
	}
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

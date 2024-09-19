/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:02:26 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/19 15:38:04 by tpassin          ###   ########.fr       */
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
	t_env	*env;
	int		j;

	env = data->get_env;
	j = 0;
	if (str[*i] == '$')
		return (NULL);
	if (str[*i] == '?')
		return ((*i += 1), ft_itoa(0));
	if (str[*i] >= '0' && str[*i] <= '9')
		return ((*i)++, NULL);
	while (str[*i + j] && (ft_isalnum(str[*i + j]) || str[*i + j] == '_'))
		j++;
	str = &str[*i];
	*i += j;
	while (env)
	{
		if (ft_strncmp(str, env->key, j) == 0 && ft_strncmp(str, env->key,
				ft_strlen(env->key)) == 0)
			return (ft_strdup(env->value));
		env = env->next;
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
				free_array(new);
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

char	*get_varenv(char *str, t_data *data, int TYPE)
{
	int		i;
	int		len;
	char	*new;
	char	*value;
	int		pos;

	if (TYPE == HERE_DOC)
		return (ft_strdup(str));
	i = 0;
	pos = 0;
	new = NULL;
	value = NULL;
	len = len_varenv(data, str);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		wordinquote(str[i], data);
		if (str[i] == '$' && str[i + 1] && data->cquote != '\''
			&& !is_quotes(str[i + 1]))
		{
			i++;
			value = get_value(str, &i, data);
			if (value)
			{
				new = ft_strncat(new, value, ft_strlen(value));
				pos += ft_strlen(value);
				free_array(value);
			}
		}
		else if (data->cquote == 'N' && str[i] == '$')
			i++;
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
	s = NULL;
	str = get_varenv(str, data, heredoc);
	if (!str)
		return (NULL);
	if (nb_quotes && str)
	{
		s = malloc(sizeof(char *) * ((ft_strlen(str) - nb_quotes) + 1));
		if (!s)
			return (free_array(str), NULL);
		while (str && str[i])
		{
			if (wquote(str[i], &i, data))
				s[j++] = str[i++];
		}
		s[j] = '\0';
		if (!s && str)
			return (free_array(str), NULL);
		return (free_array(str), s);
	}
	return (str);
}

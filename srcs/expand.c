/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:02:26 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/08 16:32:05 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *str, int *i, t_data *data)
{
	t_env	*env;
	int		j;

	env = data->get_env;
	j = 0;
	if (str[*i] == '$')
		return (NULL);
	if (str[*i] == '?')
		return ((*i += 1), ft_itoa(data->exit_status));
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
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		return (len);
	loop_len(str, data, &len, &i);
	return (len);
}

char	*get_varenv(char *str, t_data *data, int TYPE)
{
	int	i;
	int	len;
	int	pos;

	if (!str)
		return (NULL);
	if (TYPE == HERE_DOC || !ft_strchr(str, '$'))
		return (ft_strdup(str));
	i = 0;
	pos = 0;
	len = len_varenv(data, str);
	data->new = ft_calloc(sizeof(char), len + 1);
	if (!data->new)
		return (NULL);
	while (str[i] && (str[i] == '$' || is_quotes(str[i])))
		i++;
	if (str[i] == '\0')
		return (free(data->new), ft_strdup(str));
	i = 0;
	process_string(str, data, &pos, &i);
	return (data->new);
}

char	*ft_expand(t_data *data, char *str, int heredoc, int nb_quotes)
{
	int		i;
	int		j;
	char	*s;
	char	*s2;

	i = 0;
	j = 0;
	s2 = get_varenv(str, data, heredoc);
	if (!s2)
		return (NULL);
	if (nb_quotes && s2)
	{
		s = malloc(sizeof(char *) * ((ft_strlen(s2) - nb_quotes) + 1));
		if (!s)
			return (free(s2), NULL);
		while (s2 && s2[i])
		{
			if (wquote(s2[i], &i, data))
				s[j++] = s2[i++];
		}
		s[j] = '\0';
		if (!s && s2)
			return (free(s2), NULL);
		// dprintf(2, "STRING: %s LEN: %zu\n", s, ft_strlen(s));
		return (free(s2), s);
	}
	return (s2);
}

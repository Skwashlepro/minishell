/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:15:56 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 20:18:23 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

static int	count_words(const char *s, char c)
{
	int	w;
	int	t;

	w = 0;
	t = 0;
	while (*s)
	{
		if (*s != c && t == 0)
		{
			t = 1;
			w++;
		}
		if (*s == c)
			t = 0;
		s++;
	}
	return (w);
}

static char	*strdupp(const char *s, int i, int j)
{
	char	*dest;
	int		k;

	k = 0;
	dest = ft_calloc(sizeof(char), (((j - i) + 1)));
	if (!dest)
		return (NULL);
	while (i < j)
		dest[k++] = s[i++];
	dest[k] = '\0';
	return (dest);
}

char	**ft_free(char **dest, int len)
{
	if (dest)
	{
		while (len >= 0 && dest)
		{
			free(dest[len]);
			dest[len] = NULL;
			len--;
		}
		free(dest);
	}
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**dest;

	dest = ft_calloc(sizeof(char *), count_words(s, c) + 1);
	if (!s || !dest)
		return (ft_free(dest, count_words(s, c)));
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			dest[j] = strdupp(s, index, i);
			if (!(dest[j++]))
				return (ft_free(dest, j - 1));
			index = -1;
		}
	}
	dest[j] = 0;
	return (dest);
}

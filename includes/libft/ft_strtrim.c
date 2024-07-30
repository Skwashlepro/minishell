/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:03:29 by luctan            #+#    #+#             */
/*   Updated: 2024/05/06 17:18:54 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	trim_length(const char *s1, const char *set)
{
	int	start;
	int	end;

	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && is_in_set(s1[end], set))
		end--;
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*dest;

	if (!s1 || !set || !*s1)
		return (ft_strdup(""));
	i = 0;
	len = trim_length(s1, set);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	j = 0;
	while (j < len)
	{
		dest[j] = s1[i + j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

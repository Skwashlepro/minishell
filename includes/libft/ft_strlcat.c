/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:42:35 by luctan            #+#    #+#             */
/*   Updated: 2024/05/06 15:43:15 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	i = ft_strlen(dst);
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(&src[j]) + ft_strlen(dst));
}

// int	main(int ac, char **av)
// {
// 	printf("%i\n", strlcat(av[1], av[2], atoi(av[3])));
// 	printf("%i\n", ft_strlcat(av[1], av[2], atoi(av[3])));
// }

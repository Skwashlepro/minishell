/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:33:49 by luctan            #+#    #+#             */
/*   Updated: 2023/11/09 19:05:43 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const char			*s;

	d = (unsigned char *)dest;
	s = (const char *)src;
	i = -1;
	if (!dest && !src)
		return (0);
	while (++i < n)
		d[i] = s[i];
	return (dest);
}

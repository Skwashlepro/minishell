/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:02 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 20:16:28 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*td;
	const unsigned char	*ts;
	size_t				i;

	td = (unsigned char *)dest;
	ts = (unsigned char *)src;
	i = 0;
	if (td > ts)
		while (n-- > 0)
			td[n] = ts[n];
	else if (ts > td)
	{
		while (i < n)
		{
			td[i] = ts[i];
			i++;
		}
	}
	return (dest);
}

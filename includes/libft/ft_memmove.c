/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:02 by luctan            #+#    #+#             */
/*   Updated: 2023/11/15 17:35:52 by luctan           ###   ########.fr       */
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

// int	main(char **av, int ac)
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = "qqq";
// 	s2 = "asd";
// 	printf("%p\n", ft_memmove(s1, s2, 5));
// 	printf("%p\n", memmove(s1, s2, 5));
// }

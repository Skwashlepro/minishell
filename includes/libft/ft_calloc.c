/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:34:40 by luctan            #+#    #+#             */
/*   Updated: 2023/11/16 14:23:23 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*a;

	if (nmemb != 0 && ((nmemb * size) / nmemb) != size)
		return (NULL);
	a = malloc(size * nmemb);
	if (!a)
		return (NULL);
	ft_bzero(a, nmemb * size);
	return (a);
}

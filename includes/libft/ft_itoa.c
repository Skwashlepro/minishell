/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:45:40 by luctan            #+#    #+#             */
/*   Updated: 2024/10/18 20:16:40 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbsize(long nb)
{
	int	c;

	c = 0;
	if (nb < 0)
	{
		nb = -nb;
		c++;
	}
	while (nb > 0)
	{
		nb /= 10;
		c++;
	}
	return (c);
}

/*char	*zero(char *nbr)
{
	nbr[0] = '0';
	return (ft_strdup("0"));
}*/

char	*ft_itoa(int n)
{
	char	*nbr;
	long	nb;
	int		i;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	nbr = malloc(sizeof(char) * nbsize(nb) + 1);
	if (!nbr)
		return (NULL);
	i = (nbsize(nb) - 1);
	nbr[nbsize(nb)] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		nbr[0] = '-';
	}
	while (nb > 0)
	{
		nbr[i] = ((nb % 10) + 48);
		nb /= 10;
		i--;
	}
	return (nbr);
}

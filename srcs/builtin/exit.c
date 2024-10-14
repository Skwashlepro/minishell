/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:01:11 by luctan            #+#    #+#             */
/*   Updated: 2024/09/17 16:08:18 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *str, t_data *data)
{
	char	**args;
	int		i;
	long	nb;

	i = 0;
	if (i > 2)
		return ((void) !printf("minishell: exit: too many arguments\n"));
	args = ft_split(str, ' ');
	if (!args)
		return (clean_all(data), exit(0));
	while (args[i])
		i++;
	if ((i == 2 && !nb_check(args[1])))
		return (printf("minishell: exit: %s: numeric argument required\n",
				args[1]), free_tab(args), clean_all(data), exit(2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
		free_tab(args);
		return (clean_all(data), exit((int)nb));
	}
	else
		return (free_tab(args), clean_all(data), exit(0));
}
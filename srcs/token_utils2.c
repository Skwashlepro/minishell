/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:14:18 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/12 18:06:50 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_addback(t_command **command, t_command *new)
{
	t_command	*current;

	if (command)
	{
		if (*command == NULL)
			*command = new;
		else
		{
			current = *command;
			while (current->next)
				current = current->next;
			current->next = *command;
		}
	}
}

char	**ft_join_tab(char **oldtab, char *str)
{
	int		i;
	char	**newtab;

	i = 0;
	while (oldtab[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 2));
	if (!newtab)
		return (NULL);
	i = 0;
	while (oldtab[i])
	{
		newtab[i] = oldtab[i];
		i++;
	}
	newtab[i++] = str;
	newtab[i] = 0;
	return (free(oldtab), newtab);
}

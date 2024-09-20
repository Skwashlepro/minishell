/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:14:18 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/20 18:10:33 by tpassin          ###   ########.fr       */
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
	if (!oldtab)
	{
		oldtab = (char **)malloc(sizeof(char *) * (1 + 1));
		if (!oldtab || !str)
			return (NULL);
		oldtab[0] = ft_strdup(str);
		if (!oldtab[0])
			return (free_tab(oldtab), NULL);
		oldtab[1] = NULL;
		return (oldtab);
	}
	while (oldtab[i++])
	newtab = malloc(sizeof(char *) * (i + 2));
	if (!newtab)
		return (NULL);
	i = -1;
	while (oldtab[++i])
		newtab[i] = oldtab[i];
	newtab[i++] = str;
	newtab[i] = 0;
	return (free(oldtab), newtab);
}

int	is_quotes(int c)
{
	if (c != '"' && c != '\'')
		return (0);
	return (1);
}

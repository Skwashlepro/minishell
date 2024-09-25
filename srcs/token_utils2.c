/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:14:18 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/25 17:49:45 by tpassin          ###   ########.fr       */
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
			current->next = new;
		}
	}
}

void	redirection_addback(t_redir **redir, t_redir *new)
{
	t_redir	*current;

	if (redir)
	{
		if (*redir == NULL)
			*redir = new;
		else
		{
			current = *redir;
			while (current->next)
				current = current->next;
			current->next = new;
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
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		oldtab = (char **)malloc(sizeof(char *) * (1 + 1));
		if (!oldtab || !str)
			return (NULL);
		oldtab[0] = str;
		if (!oldtab[0])
			return (free_tab(oldtab), NULL);
		oldtab[1] = NULL;
		return (oldtab);
	}
	while (oldtab && oldtab[i++])
		newtab = malloc(sizeof(char *) * (i + 2));
	if (!newtab)
		return (free(oldtab), NULL);
	i = -1;
	while (oldtab && oldtab[++i])
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

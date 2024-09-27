/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:42:49 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/27 20:26:08 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_here_doc(t_command *cmd, char *lim)
{
	int		fd;
	char	*str;

	cmd->redirection->type = HERE_DOC;
	fd = open(">", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), exit(1));
	while (1)
	{
		ft_printf(1, ">");
		str = get_next_line(0, 1);
		if (!str)
			break ;
		if (ft_strncmp(str, lim, ft_strlen(lim)) == 0
			&& str[ft_strlen(lim)] == '\n')
		{
			free(str);
			break ;
		}
		ft_printf(fd, "%s", str);
		free(str);
	}
	close(fd);
}

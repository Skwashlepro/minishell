/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:42:49 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/28 18:03:10 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_name(t_data *data)
{
	char	*str;

	str = ft_strjoin(GET_HEREDOC, ft_itoa(data->heredoc));
	if (!str)
		return (NULL);
	return (str);
}

void	ft_here_doc(t_command *cmd, char *lim, t_data *data)
{
	int		fd;
	char	*str;
	char	*name;

	(void)cmd;
	name = generate_name(data);
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), exit(1));
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, lim) == 0)
		{
			free(str);
			break ;
		}
		ft_printf(fd, "%s\n", str);
		free(str);
	}
	data->cmd->redirection->heredoc_name = name;
	close(fd);
}

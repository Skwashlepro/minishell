/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:42:49 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/01 16:14:51 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_name(t_data *data)
{
	char	*str;
	char	*s;

	str = NULL;
	s = NULL;
	s = ft_itoa(data->heredoc);
	if (!s)
		return (NULL);
	str = ft_strjoin(GET_HEREDOC, s);
	if (!str)
		return (free(s), NULL);
	return (free(s), str);
}

void	ft_here_doc(t_redir *redir, t_data *data)
{
	int		fd;
	char	*str;
	char	*name;

	name = generate_name(data);
	if (!name)
		return ;
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), exit(1));
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, redir->file) == 0)
		{
			free(str);
			break ;
		}
		ft_printf(fd, "%s\n", str);
		free(str);
	}
	close(fd);
	redir->heredoc_name = ft_strdup(name);
	free(name);
}

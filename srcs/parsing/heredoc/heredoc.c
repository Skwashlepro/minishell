/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:42:49 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/18 18:45:11 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_name(t_data *data)
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

void	loop_heredoc(char *filename, t_data *data, int fd, t_redir *redir)
{
	char	*name;

	name = NULL;
	while (1)
	{
		filename = readline("> ");
		if (!filename)
		{
			dup2(data->save, STDIN_FILENO);
			close(data->save);
			break ;
		}
		if (ft_strcmp(filename, redir->file) == 0)
		{
			close(data->save);
			free(filename);
			break ;
		}
		data->in_heredoc++;
		name = get_varenv(filename, data, WORD);
		ft_printf(fd, "%s\n", name);
		free(filename);
		free(name);
	}
	data->in_heredoc = 0;
}

static int	ft_here_doc(t_redir *redir, t_data *data)
{
	int		fd;
	char	*str;

	str = NULL;
	redir->heredoc_name = generate_name(data);
	if (!redir->heredoc_name)
		return (1);
	fd = open(redir->heredoc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), 1);
	sig_heredoc(data);
	g_var = 0;
	data->save = dup(STDIN_FILENO);
	loop_heredoc(str, data, fd, redir);
	close(fd);
	if (g_var == 130)
		return (1);
	return (0);
}

int	run_heredoc(t_command *cmd, t_data *data)
{
	t_command	*tmp;
	t_redir		*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->redirection;
		while (redir)
		{
			if (redir->type == HERE_DOC)
			{
				if (ft_here_doc(redir, data))
					return (1);
				data->heredoc--;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:31:24 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/10 16:33:35 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close(int *fd)
{
	if (*fd > 2 && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	handle_sig_in_heredoc(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		ft_close(&fd);
		ft_printf(STDERR_FILENO, "\n");
		g_var = 130;
	}
}

void	sig_heredoc(t_data *data)
{
	(void)data;
	signal(SIGINT, handle_sig_in_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

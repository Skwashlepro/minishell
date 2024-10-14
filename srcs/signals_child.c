/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:19:00 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/10 18:29:20 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_var = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_var = 131;
		ft_printf(2, "Quit (core dumped)\n");
	}
}

void	signal_child_ctrl_c(void)
{
	struct sigaction	child_ctrl_c;

	child_ctrl_c.sa_handler = sig_handler;
	child_ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&child_ctrl_c.sa_mask);
	if (sigaction(SIGINT, &child_ctrl_c, NULL) == -1)
		ft_printf(2, "ERROR SIGINT\n");
}

void	signal_child_backslash(void)
{
	struct sigaction	child_ctrl_back;

	child_ctrl_back.sa_handler = sig_handler;
	child_ctrl_back.sa_flags = SA_RESTART;
	sigemptyset(&child_ctrl_back.sa_mask);
	if (sigaction(SIGQUIT, &child_ctrl_back, NULL) == -1)
		ft_printf(2, "ERROR SIGQUIT\n");
}

void	child_signals(void)
{
	signal_child_ctrl_c();
	signal_child_backslash();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:19:00 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/04 20:58:05 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_child_ctrl_c(void)
{
	struct sigaction	child_ctrl_c;

	g_var = 130;
	child_ctrl_c.sa_handler = SIG_DFL;
	child_ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&child_ctrl_c.sa_mask);
	if (sigaction(SIGINT, &child_ctrl_c, NULL) == -1)
		ft_printf(2, "ERROR SIGINT\n");
}

void	signal_child_backslash(void)
{
	struct sigaction	child_ctrl_back;

    g_var = 131;
	child_ctrl_back.sa_handler = SIG_DFL;
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
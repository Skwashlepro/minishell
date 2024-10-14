/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:30:51 by tpassin           #+#    #+#             */
/*   Updated: 2024/10/12 20:01:32 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inthandler(int sig)
{
	(void)sig;
	(void)!write(1, "\n", 1);
	g_var = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_ctrl_c(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = inthandler;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
		ft_printf(2, "ERROR SIGINT\n");
}

static void	signal_backslash(void)
{
	struct sigaction	ctrl_back;

	ctrl_back.sa_handler = SIG_IGN;
	ctrl_back.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_back.sa_mask);
	if (sigaction(SIGQUIT, &ctrl_back, NULL) == -1)
		ft_printf(2, "ERROR SIGQUIT\n");
}

void	ft_signal(void)
{
	signal_ctrl_c();
	signal_backslash();
}

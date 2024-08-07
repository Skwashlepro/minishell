/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:30:51 by tpassin           #+#    #+#             */
/*   Updated: 2024/08/07 19:16:13 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_msg(char *str)
{
    ft_putstr_fd("Error ", 2);
    ft_putstr_fd(str, 2);
    exit (1);
}

static void	INThandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_var = 130;
	return ;
}

void	ft_signal(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = INThandler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
        error_msg("SIGINT");
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
        error_msg("SIGQUIT");
}
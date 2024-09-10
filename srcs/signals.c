/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:30:51 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/10 17:38:42 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *str)
{
	ft_putstr_fd("Error ", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

static void	inthandler(int sig)
{
	(void)sig;
	(void)!write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_var = 130;
	return ;
}

void	ft_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = inthandler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_msg("SIGINT\n");
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		error_msg("SIGQUIT\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:22:28 by luctan            #+#    #+#             */
/*   Updated: 2024/08/15 18:15:26 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_var;

typedef enum s_token_type
{
	WORD,
	PIPE,
	INFILE,
	OUTFILE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
}			t_token_type;

typedef struct s_data
{
	char	**env;
	char	*prompt;

}			t_data;

int			check_input(char *str, t_data *data);
void		print_env(t_data *data);
void		ft_signal(void);
void		init_env(t_data *data, char **envp, int ac);
int			is_space(char c);
int			inquotes(char c, int i);
void		ft_exit(char *str);
void		free_tab(char **str);
long long	ft_atol(const char *nb);

#endif
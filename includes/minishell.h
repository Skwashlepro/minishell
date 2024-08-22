/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:22:28 by luctan            #+#    #+#             */
/*   Updated: 2024/08/22 19:13:30 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	CMD,
	ARG,
	WORD,
	PIPE,
	INFILE,
	OUTFILE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	LIMITER,
	ENV_VAR,
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	**env;
	char	*prompt;
	t_token	*head;

}	t_data;

int		check_input(char *str, t_data *data);
void	print_env(t_data *data);
void	ft_signal(void);
void	init_env(t_data *data, char **envp, int ac);
void	init_data(t_data *data);
int		is_space(char c);
int		inquotes(char c, int i);
void	ft_exit(char *str);
void	free_tab(char **str);
long	ft_atol(char **nb);
void	word_token(char **tab, t_data *data);
int		tokenizer(t_data *data, char *input);
void	add_token(t_token **token_head, t_token_type type, char *str);
void	free_array(char *str);

#endif
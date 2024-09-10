/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:47:15 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/10 18:04:30 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_check(char *str)
{
	int	error;
	int	i;

	i = 0;
	error = 1;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			error = 0;
			break ;
		}
		i++;
	}
	return (error);
}

void	ft_exit(char *str, t_data *data)
{
	char	**args;
	int		i;
	long	nb;

	i = 0;
	if (i > 2)
		return ((void)!printf("minishell: exit: too many arguments\n"));
	args = ft_split(str, ' ');
	if (!args)
		return (ft_clean(data), free_env(data), exit(0));
	while (args[i])
		i++;
	if ((i == 2 && !nb_check(args[1])))
		return (printf("minishell: exit: %s: numeric argument required\n",
				args[1]), free_tab(args), ft_clean(data),
			free_env(data), exit(2));
	else if (i == 2)
	{
		nb = ft_atol(args);
		while (nb < 0)
			nb += 256;
		free_tab(args);
		return (ft_clean(data), free_env(data), exit((int)nb));
	}
	else
		return (free_tab(args), ft_clean(data), 
			exit(0));
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	inquotes(char c, int i)
{
	static int	dq = 0;
	static int	sq = 0;

	if (c == '"' && !sq)
		dq = !dq;
	else if (c == '\'' && !dq)
		sq = !sq;
	i = (dq || sq);
	return (i);
}

void	char_redir(char *str, int *redir_out, int *redir)
{
	if (*str == '<')
		(*redir)++;
	else if (*str == '>')
		(*redir_out)++;
	else if (ft_isalnum(*str) && *redir <= 2 && !(*redir_out))
		*redir = 0;
	else if (ft_isalnum(*str) && *redir_out <= 2 && !(*redir))
		*redir_out = 0;
}

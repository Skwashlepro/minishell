/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:53:16 by luctan            #+#    #+#             */
/*   Updated: 2024/10/10 03:44:43 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_env *old, t_env *pwd)
{
	if (pwd)
	{
		if (old)
		{
			free_array(old->value);
			old->value = NULL;
			old->value = ft_strdup(pwd->value);
		}
		free_array(pwd->value);
		pwd->value = NULL;
		pwd->value = getcwd(pwd->value, 0);
	}
}

t_env	*search_key(t_env *get_env, char *key)
{
	t_env	*tmp;

	tmp = get_env;
	if (!tmp)
		return (NULL);
	while (ft_strcmp(tmp->key, key) && tmp->next)
		tmp = tmp->next;
	if (!ft_strcmp(tmp->key, key))
		return (tmp);
	else
		return (NULL);
}

int	args_errors(t_env *old_pwd, char **args)
{
	if (args[1])
		if (!old_pwd && !ft_strcmp(args[1], "-"))
			return ((void)ft_printf(2, "minishell$ cd: OLDPWD not set\n"), 1);
	if (count_args(args) == 3)
		return ((void)ft_printf(2, "%s%s\n", "cd: string not in pwd: ",
				args[1]), 1);
	if (count_args(args) > 3)
		return ((void)ft_printf(2, "cd: too many arguments\n"), 1);
	return (0);
}

void	cd(t_data *data, char **args)
{
	t_env	*old_pwd;
	t_env	*tmp;
	t_env	*pwd;

	tmp = NULL;
	old_pwd = search_key(data->get_env, "OLDPWD");
	pwd = search_key(data->get_env, "PWD");
	if (args_errors(old_pwd, args))
		return ;
	if (count_args(args) == 1)
	{
		tmp = search_key(data->get_env, "HOME");
		if (!tmp)
			return ((void)ft_printf(2, "minishell$ cd: HOME not set\n"));
		if (chdir(tmp->value) != -1)
			update_env(old_pwd, pwd);
		return ;
	}
	if (old_pwd && !ft_strcmp(args[1], "-"))
		return ((void)chdir(old_pwd->value));
	if (chdir(args[1]) == -1)
		return ((void)ft_printf(2,
				"minishell$ cd: No such file or directory\n"));
	update_env(old_pwd, pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:53:16 by luctan            #+#    #+#             */
/*   Updated: 2024/10/03 00:55:19 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_env *old, char *new)
{
	if (old->value)
		free(old->value);
	old->value = ft_strdup(new);
}

t_env *search_key(t_env *get_env, char *key)
{
	t_env *tmp;

	tmp = get_env;
	if (!tmp)
		return (NULL);
	while (ft_strcmp(tmp->key, key) && tmp)
		tmp = tmp->next;
	if (!ft_strcmp(tmp->key, key))
		return (tmp);
	else
		return (NULL);
}

void	cd(t_data *data, char **args)
{
	t_env	*old_pwd;
	t_env	*tmp;
	t_env	*pwd;

	tmp = NULL;
	old_pwd = search_key(data->get_env, "OLDPWD");
	pwd = search_key(data->get_env, "PWD");
	if (count_args(args) == 3)
		return ((void)printf("%s%s\n", "cd: string not in pwd: ", args[1]));
	if (count_args(args) > 3)
		return ((void)printf("cd: too many arguments\n"));
	if (count_args(args) == 1)
	{
		tmp = search_key(data->get_env, "HOME");
		if (!tmp)
			return ((void)printf("$minishell cd: HOME not set\n"));
		update_env(old_pwd, pwd->value);
		update_env(pwd, tmp->value);
		chdir(tmp->value);
		return ;
	}
	if (!ft_strcmp(args[1], "-"))
		return ((void)chdir(old_pwd->value));
	else if (chdir(args[1]))
		return ((void)printf("minishell$ cd: No such file or directory\n"));
	update_env(old_pwd, pwd->value);
	update_env(pwd, args[1]);
	return ;
}

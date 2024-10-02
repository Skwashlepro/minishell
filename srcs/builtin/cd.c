/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:53:16 by luctan            #+#    #+#             */
/*   Updated: 2024/10/02 20:10:37 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*oldpwd(t_data *data)
{
	t_env *tmp;
	char *pwd;

	pwd = "PWD";
	tmp = data->get_env;
	while (tmp->key != pwd && tmp)
		tmp = tmp->next;
	return (tmp->value);
}

t_env *search_key(t_env *get_env, char *key)
{
	t_env *tmp;

	tmp = get_env;
	while (tmp->key != key && tmp)
		tmp = tmp->next;
	if (tmp->key == key)
		return (tmp);
	else
		return (NULL);
}

void	cd(t_data *data, char *args)
{
	t_env	*old_pwd;
	t_env	*tmp;
	t_env	*pwd;

	tmp = NULL;
	old_pwd = search_key(data->get_env, "OLDPWD");
	pwd = search_key(data->get_env, "PWD");
	if (!ft_strcmp(args, "-"))
		return ((void)chdir(old_pwd->value));
	if (args)
	{
		tmp = search_key(data->get_env, "HOME");
		if (!tmp)
			return ((void)printf("$minishell cd: HOME not set\n"));
		old_pwd->value = pwd->value;
		pwd->value = tmp->value;
		chdir(tmp->value);
		return ;
	}
	if (chdir(args) == -1)
		return ((void)printf("$minishell cd: No such file or directory\n"));
	old_pwd->value = pwd->value;
	pwd->value = args;
	return ;
}

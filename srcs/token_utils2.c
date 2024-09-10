/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:14:18 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/10 17:37:48 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_join_tab(char **oldtab, char *str)
{
    int i;
    char **newtab;

    i = 0;
    while (oldtab[i])
        i++;
    newtab = malloc(sizeof(char *) * (i + 2));
    if (!newtab)
        return (NULL);
    i = 0;
    while (oldtab[i])
    {
        newtab[i] = oldtab[i];
        i++;
    }
    newtab[i++] = str;
    newtab[i] = 0;
    return (free(oldtab), newtab);   
}
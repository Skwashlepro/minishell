/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:47:02 by tpassin           #+#    #+#             */
/*   Updated: 2024/09/23 16:59:40 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int size_command(t_command *command)
{
    int i;

    i = 0;
    while (command->next)
    {
        command = command->next;
        i++;
    }
    return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttelolah <ttelolah@student.42antananavo    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:37 by erijania          #+#    #+#             */
/*   Updated: 2024/12/10 20:04:03 by ttelolah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "msutils.h"

static int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (-1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
int built_unset(t_mini *mini, char **args)
{
    t_env   *prev;
    t_env   *current;
    int     i;

    i = 1;
    while (args[i])
    {
        prev = NULL;
        current = mini->env_list;
        while (current)
        {
            if (ft_strcmp(current->name, args[i]) == 0)
            {
                if (prev)
                    prev->next = current->next;
                else
                    mini->env_list = current->next;
                free(current->name);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    return (0);
}

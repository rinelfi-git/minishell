/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 08:17:09 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 15:35:06 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    built_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
    return (1);
}

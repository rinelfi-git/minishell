/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 08:17:09 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 08:20:09 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    built_env(t_mini *mini)
{
    t_env   *env;

    env = mini->env;
    while (env)
    {
        printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
}

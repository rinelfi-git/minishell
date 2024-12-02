/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 08:17:09 by erijania          #+#    #+#             */
/*   Updated: 2024/12/02 16:28:30 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_env(t_env *env)
{
	while (env)
	{
		if (env->name && env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (1);
}

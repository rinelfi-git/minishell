/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 08:17:09 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 13:47:04 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_env(t_mini *mini)
{
	t_env	*env;

	env = mini->env_list;
	while (env)
	{
		if (env->name && env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	mini->exit_code = 0;
	return (1);
}

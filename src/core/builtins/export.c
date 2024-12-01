/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:26 by erijania          #+#    #+#             */
/*   Updated: 2024/12/01 15:24:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

static void	print_env(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->name);
		if (env->value)
			printf("=%s\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

int	    built_export(t_env *env, char **args)
{
	int	i;
	int	len;

	len = arg_len(args);
	if (len == 1)
		print_env(env);
	else
	{
		while (args[i])
			printf("ENV[%s]\n", args[i++]);	
	}
	return (1);
}

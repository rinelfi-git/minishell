/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:26 by erijania          #+#    #+#             */
/*   Updated: 2024/12/01 16:33:23 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

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

static int	has_value(char *str)
{
	while (*str)
	{
		if (*(str++) == '=')
			return (1);
	}
	return (0);
}

static int	do_export(t_env *env, char *str)
{
	int		i;
	char	*var;
	t_env	*get;

	i = 0;
	get = 0;
	if (!has_value(str) && !ft_getenv(env, str))
		append_env(&env)->name = ft_strdup(str);
	else
	while (str[i] && !get)
	{
		if (str[i] == '=')
		{
			var = ft_substr(str, 0, i);
			get = env_get(&env, var);
			if (get)
			{
				free(get->value);
				get->value = ft_substr(str, i + 1, ft_strlen(str + i));
			}
			else
			{
				get = append_env(&env);
				get->name = ft_strdup(var);
				get->value = ft_substr(str, i + 1, ft_strlen(str + i));
			}
			free(var);
		}
		i++;
	}
	return (1);
}

int	    built_export(t_env *env, char **args)
{
	int	i;

	if (len_strarray(args) == 1)
		print_env(env);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!do_export(env, args[i++]))
				return (0);
		}
	}
	return (1);
}

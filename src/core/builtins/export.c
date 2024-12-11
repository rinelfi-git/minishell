/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:26 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 10:19:19 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static void	export_print(t_env *env)
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

static int	export_assign(char *str, int i, t_env **env)
{
	char	*var;
	t_env	*get;

	var = ft_substr(str, 0, i);
	get = env_get(env, var);
	if (get)
	{
		free(get->value);
		get->value = ft_substr(str, i + 1, ft_strlen(str + i + 1));
	}
	else
	{
		get = append_env(env);
		get->name = ft_strdup(var);
		get->value = ft_substr(str, i + 1, ft_strlen(str + i + 1));
	}
	free(var);
	return (1);
}

static int	export_append(char *str, int i, t_env **env)
{
	char	*var;
	char	*new;
	t_env	*get;

	var = ft_substr(str, 0, i);
	get = env_get(env, var);
	if (get)
	{
		new = ft_substr(str, i + 2, ft_strlen(str + (i + 2)));
		str_append(&(get->value), new);
		free(new);
	}
	else
	{
		get = append_env(env);
		get->name = ft_strdup(var);
		get->value = ft_substr(str, i + 2, ft_strlen(str + i + 2));
	}
	free(var);
	return (1);
}

static int	do_export(t_env *env, char *str)
{
	int	i;
	int	has_operation;

	i = -1;
	has_operation = 0;
	while (str[++i] && !has_operation)
		if (str[i] == '=')
			has_operation = 1;
	if (!has_operation && !ft_getenv(env, str))
		append_env(&env)->name = ft_strdup(str);
	else
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] == '=')
				return (export_assign(str, i, &env));
			else if (str[i] == '+' && str[i + 1] == '=')
				return (export_append(str, i, &env));
		}
	}
	return (1);
}

int	built_export(t_env *env, char **args)
{
	int	i;

	if (strarraylen(args) == 1)
		export_print(env);
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

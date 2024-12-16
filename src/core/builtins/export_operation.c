/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:31:54 by erijania          #+#    #+#             */
/*   Updated: 2024/12/16 15:31:55 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

void	export_print(t_env *env)
{
	while (env)
	{
		printf("export %s", env->name);
		if (env->value)
			printf("=%s\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

int	export_append(char *str, int i, t_env **env)
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

int	export_assign(char *str, int i, t_env **env)
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

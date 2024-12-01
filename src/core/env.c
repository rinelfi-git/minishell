/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:50:38 by erijania          #+#    #+#             */
/*   Updated: 2024/12/01 08:28:33 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"
#include <stdlib.h>

static int	env_length(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_array(t_mini *mini)
{
	int		len;
	int		i;
	char	**out;
	t_env	*env;

	len = env_length(mini->env_list);
	out = malloc(sizeof(char *) * (len + 1));
	if (!out)
		return (0);
	env = mini->env_list;
	i = 0;
	while (i < len)
	{
		out[i] = ft_strdup(env->name);
		str_append(out + i, "=");
		str_append(out + i, env->value);
		i++;
		env = env->next;
	}
	out[i] = 0;
	return (out);
}

char	*ft_getenv(t_env *env, char *var)
{
	char	*val;
	size_t	length;

	val = 0;
	length = ft_strlen(var);
	while (env && !val)
	{
		if (ft_strncmp(env->name, var, length) == 0)
			val = env->value;
		env = env->next;
	}
	return (val);
}

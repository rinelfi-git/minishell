/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:50:38 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 13:01:24 by erijania         ###   ########.fr       */
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

	len = env_length(mini->env);
	out = malloc(sizeof(char *) * (len + 1));
	if (!out)
		return (0);
	env = mini->env;
	i = 0;
	while (i < len)
	{
		out[i] = ft_strdup(env->name);
		str_append(out + i, "=");
		str_append(out + i, env->value);
		i++;
		env = env->next;
	}
	return (out);
}

char	*ft_getenv(t_mini *mini, char *var)
{
	char	*val;
	t_env	*loop;
	size_t	length;

	loop = mini->env;
	val = 0;
	length = ft_strlen(var);
	while (loop && !val)
	{
		if (ft_strncmp(loop->name, var, length) == 0)
			val = loop->value;
		loop = loop->next;
	}
	return (val);
}

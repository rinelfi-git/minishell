/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:50:38 by erijania          #+#    #+#             */
/*   Updated: 2024/12/02 16:03:55 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

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

t_env	*append_env(t_env **head)
{
	t_env	*new;
	t_env	*tmp;

	if (!head)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = 0;
	new->value = 0;
	new->next = 0;
	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_env	*env_get(t_env **head, char *name)
{
	t_env	*env;

	env = *head;
	while (env)
	{
		if (ft_strncmp(name, env->name, INT_MAX) == 0)
			return (env);
		env = env->next;
	}
	return (0);
}

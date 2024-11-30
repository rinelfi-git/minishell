/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:50:38 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 09:39:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
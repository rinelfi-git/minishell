/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:27:04 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 14:45:59 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"
#include <stdlib.h>

static int	arg_len(char **args)
{
	int	len;

	len = 0;
	while (args && args[len])
		len++;
	return (len);
}

static int	append_arg(t_mini *mini, char ***args, char *str)
{
	char	**tmp;
	int		i;
	int		len;

	if (!str)
		return (0);
	len = arg_len(*args);
	tmp = malloc(sizeof(char **) * (len + 2));
	if (!tmp)
		return (0);
	i = -1;
	while (++i < len)
	{
		tmp[i] = ft_strdup((*args)[i]);
		parse(mini, tmp + i);
	}
	tmp[i] = ft_strdup(str);
	parse(mini, tmp + (i++));
	tmp[i] = 0;
	free_strarray(*args);
	*args = tmp;
	return (1);
}

char	**get_cmd_params(t_mini *mini, t_token *token)
{
	char	**out;

	out = 0;
	while (token && token->type != PIPE)
	{
		if (is_special(token->str) && token->type != PIPE && token->next)
			token = token->next->next;
		else if (token && !append_arg(mini, &out, token->str))
		{
			free_strarray(out);
			return (0);
		}
		else if (token)
			token = token->next;
	}
	return (out);
}

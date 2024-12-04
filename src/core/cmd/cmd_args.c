/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:27:04 by erijania          #+#    #+#             */
/*   Updated: 2024/12/04 09:57:06 by erijania         ###   ########.fr       */
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

static int	append_arg(char ***args, char *str)
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
		tmp[i] = ft_strdup((*args)[i]);
	tmp[i++] = ft_strdup(str);
	tmp[i] = 0;
	free_strarray(*args);
	*args = tmp;
	return (1);
}
/**
 * @brief Si c'est un caractère spécial, sûrement un indicateur input ou output
 * et toujours, le caractère qui suit est le délimiteur ou le nom du fichier source/destination
 * donc on passe au deuxième caractère.
 * Si c'est un simple caractère, on le considère comme un vrai argument
 * 
 * @param token 
 * @return char** 
 */
char	**get_cmd_params(t_token *token)
{
	char	**out;

	out = 0;
	while (token && token->type != PIPE)
	{
		if (is_special(token->str) && token->type != PIPE && token->next)
			token = token->next->next;
		else if (token && !append_arg(&out, token->str))
		{
			free_strarray(out);
			return (0);
		}
		else if (token)
			token = token->next;
	}
	return (out);
}

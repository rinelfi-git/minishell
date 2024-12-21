/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first_special.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:49 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 11:58:53 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"
#define BUFFER_LEN 5

int escape_special(char **out, int type, int start)
{
	char	special[BUFFER_LEN];
	char	*tmp;
	int		length;

	ft_bzero(special, BUFFER_LEN);
	special[0] = '\'';
	if (type == PIPE || type == TRUNC || type == INPUT)
	{
		special[1] = (*out)[start];
		length = 1;
	}
	else
	{
		ft_strlcat(special, (*out) + start, 4);
		length = 2;
	}
	ft_strlcat(special, "'", BUFFER_LEN);
	tmp = ft_substr(*out, 0, start);
	str_append(&tmp, special);
	str_append(&tmp, (*out) + (start + length));
	free(*out);
	*out = tmp;
	escape_quote(out, start + ft_strlen(special) + 1);
	return (1);
}

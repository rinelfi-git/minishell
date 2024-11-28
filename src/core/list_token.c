/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:57:09 by erijania          #+#    #+#             */
/*   Updated: 2024/11/28 16:19:50 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	token_new(t_token **out, char *str, int type)
{
	if (!str)
		return (0);
	(*out) = malloc(sizeof(t_token));
	if (!(*out))
		return (0);
	(*out)->str = str;
	(*out)->type = type;
	(*out)->next = 0;
	return (1);
}

void	token_append(t_token **head, char *str, int type)
{
	t_token	*new;
	t_token	**last;

	if (!token_new(&new, str, type))
		return ;
	if (!(*head))
		*head = new;
	else
	{
		last = head;
		while ((*last))
			last = &(*last)->next;
		(*last) = new;
	}
}

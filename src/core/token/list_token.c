/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:57:09 by erijania          #+#    #+#             */
/*   Updated: 2024/12/01 11:18:59 by erijania         ###   ########.fr       */
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
	(*out)->prev = 0;
	(*out)->next = 0;
	return (1);
}

t_token	*token_append(t_token **head, char *str, int type)
{
	t_token	*new;
	t_token	**last;

	if (!token_new(&new, str, type))
		return (0);
	if (!(*head))
		*head = new;
	else
	{
		last = head;
		while ((*last))
		{
			new->prev = *last;
			last = &(*last)->next;
		}
		(*last) = new;
		if (new->prev->type == PIPE)
			new->type = CMD;
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:41:38 by erijania          #+#    #+#             */
/*   Updated: 2024/12/01 08:12:24 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	cmd_new(t_cmd **out)
{
	(*out) = malloc(sizeof(t_cmd));
	if (!(*out))
		return (0);
	(*out)->args = 0;
	(*out)->path = 0;
	(*out)->fd_in = -2;
	(*out)->fd_out = -2;
	(*out)->prev = 0;
	(*out)->next = 0;
	return (1);
}

t_cmd	*cmd_append(t_cmd **head)
{
	t_cmd	*new;
	t_cmd	**last;

	if (!cmd_new(&new))
		return (0);
	if (!(*head))
		*head = new;
	else
	{
		last = head;
		while ((*last))
		{
			new->prev = *last;
			last = &((*last)->next);
		}
		(*last) = new;
	}
	return (new);
}

int	cmd_length(t_cmd *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

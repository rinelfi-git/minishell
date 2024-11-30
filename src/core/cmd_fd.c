/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:59:15 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 12:28:55 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	open_file(char *path, int type)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(path, O_RDONLY);
	else if (type == APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == TRUNC)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	get_fdin(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == PIPE)
			return (STDOUT_FILENO);
		if (token->type == INPUT)
			return (open_file(token->next->str, INPUT));
		if (token->type == HEREDOC)
			return (open_file(token->next->str, INPUT));
		token = token->next;
	}
	return (-2);
}

int	get_fdout(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == TRUNC)
			return (open_file(token->next->str, TRUNC));
		if (token->type == APPEND)
			return (open_file(token->next->str, APPEND));
		token = token->next;
	}
	return (-2);
}

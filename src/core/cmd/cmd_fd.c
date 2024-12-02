/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:59:15 by erijania          #+#    #+#             */
/*   Updated: 2024/12/02 16:58:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	open_file(t_mini *mini, int *fd, char *path, int type)
{
	if (*fd >= 0)
		close(*fd);
	if (type == INPUT)
		*fd = open(path, O_RDONLY);
	else if (type == APPEND)
		*fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == TRUNC)
		*fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == HEREDOC)
		*fd = open_heredoc(mini, path);
	if (*fd == -1)
		return (0);
	return (1);
}

int	get_fdin(t_mini *mini, t_token *token)
{
	int	fd;

	fd = -2;
	while (token && token->type != PIPE)
	{
		if (token->type == INPUT)
			open_file(0, &fd, token->next->str, INPUT);
		if (token->type == HEREDOC)
			open_file(mini, &fd, token->next->str, HEREDOC);
		token = token->next;
	}
	return (fd);
}

int	get_fdout(t_token *token)
{
	int	fd;

	fd = -2;
	while (token && token->type != PIPE)
	{
		if (token->type == TRUNC)
			open_file(0, &fd, token->next->str, TRUNC);
		if (token->type == APPEND)
			open_file(0, &fd, token->next->str, APPEND);
		token = token->next;
	}
	return (fd);
}

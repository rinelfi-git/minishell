/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:59:15 by erijania          #+#    #+#             */
/*   Updated: 2024/12/16 03:51:20 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"

static int	open_file(t_mini *mini, int *fd, char *path, int type)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -2;
	if (type == INPUT)
		*fd = open(path, O_RDONLY);
	else if (type == APPEND)
		*fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == TRUNC)
		*fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == HEREDOC)
		*fd = open_heredoc(mini, path);
	if (*fd == -1 && errno)
	{
		if (errno)
		{
			fd_error(path);
			mini->exit_code = 1;
		}
		return (0);
	}
	return (1);
}

int	get_fdin(t_mini *mini, t_token *token)
{
	int	fd;

	fd = -2;
	while (token && token->type != PIPE)
	{
		if (signal_manager(0, GET_MODE) == SIGINT)
			return (-1);
		if (token->type == INPUT)
		{
			parse(mini, &token->next->str, 1);
			if (!open_file(mini, &fd, token->next->str, INPUT))
				return (-1);
		}
		if (token->type == HEREDOC)
			open_file(mini, &fd, token->next->str, HEREDOC);
		token = token->next;
	}
	return (fd);
}

int	get_fdout(t_mini *mini, t_token *token)
{
	int	fd;

	fd = -2;
	while (token && token->type != PIPE)
	{
		if (signal_manager(0, GET_MODE) == SIGINT)
			return (-1);
		if (token->type == TRUNC)
		{
			parse(mini, &(token->next->str), 1);
			if (!open_file(mini, &fd, token->next->str, TRUNC))
				return (-1);
		}
		if (token->type == APPEND)
		{
			parse(mini, &(token->next->str), 1);
			if (!open_file(mini, &fd, token->next->str, APPEND))
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:59:15 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 13:37:05 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"

static int	open_file(t_mini *mini, int *fd, char *path, int type)
{
	int	temp_fd;

	if (fd && *fd >= 0)
		close(*fd);
	temp_fd = -2;
	if (path && type == INPUT)
		temp_fd = open(path, O_RDONLY);
	else if (path && type == APPEND)
		temp_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (path && type == TRUNC)
		temp_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (path && type == HEREDOC)
		temp_fd = open_heredoc(mini, path);
	if (fd)
		*fd = temp_fd;
	else if (temp_fd >= 0)
		close(temp_fd);
	if (temp_fd == -1 && errno)
	{
		ms_perror(path);
		mini->exit_code = 1;
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
		if (token->type == TRUNC || token->type == APPEND)
		{
			parse(mini, &token->next->str, 1);
			if (!open_file(mini, 0, token->next->str, token->type))
				return (-1);
		}
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
		if (token->type == APPEND || token->type == TRUNC)
		{
			parse(mini, &(token->next->str), 1);
			if (!open_file(mini, &fd, token->next->str, token->type))
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

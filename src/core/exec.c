/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:44:50 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 13:44:21 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	redirect_in_out(t_cmd *cmd, int *pipes)
{
	close(pipes[0]);
	if (cmd->fd_in >= 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next)
		dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
}

static void	child_process(t_mini *mini, t_cmd *cmd, int *pipes)
{
	char	*path;
	char	**env;

	redirect_in_out(cmd, pipes);
	path = get_path(mini, cmd->args[0]);
	env = env_array(mini);
	execve(path, cmd->args, env);
}

static void	parent_process(t_cmd *cmd, int *pipes)
{
	close(pipes[1]);
	if (cmd->fd_out == -2)
		cmd->fd_out = pipes[0];
	if (cmd->next && cmd->next->fd_in == -2)
		cmd->next->fd_in = pipes[0];
	else
		close(pipes[0]);
}

void	mini_exec(t_mini *mini)
{
	int		fds[2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = mini->cmd;
	while (cmd)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
			child_process(mini, cmd, fds);
		else if (pid > 0)
			parent_process(cmd, fds);
		cmd = cmd->next;
		wait(0);
	}
}

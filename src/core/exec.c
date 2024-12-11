/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:44:50 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 09:39:53 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static void	redirect_in_out(t_cmd *cmd, int *pp)
{
	close(pp[0]);
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
		dup2(pp[1], STDOUT_FILENO);
	close(pp[1]);
}

static void	fork_builtin(t_mini *mini, t_cmd *cmd, int *pp)
{
	close(pp[0]);
	if (cmd->fd_out < 0 && cmd->next)
		cmd->fd_out = pp[1];
	else
		close(pp[1]);
	builtin(mini, cmd);
}

static void	child_process(t_mini *mini, t_cmd *cmd, int *pp)
{
	char	*path;

	if (is_builtin(cmd))
		fork_builtin(mini, cmd, pp);
	else if (cmd->args)
	{
		redirect_in_out(cmd, pp);
		path = get_path(mini->env_list, cmd);
		if (path)
			execve(path, cmd->args, mini->env_array);
		else
			command_not_found(mini, cmd->args[0]);
	}
	exit(mini->exit_code);
}

static void	parent_process(t_mini *mini, t_cmd *cmd, int *pp)
{
	int	wstatus;

	close(pp[1]);
	if (cmd->fd_out == -2)
		cmd->fd_out = pp[0];
	if (cmd->next && cmd->next->fd_in == -2)
		cmd->next->fd_in = pp[0];
	else
		close(pp[0]);
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		mini->exit_code = WEXITSTATUS(wstatus);
}

void	mini_exec(t_mini *mini)
{
	int		fds[2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = mini->cmd;
	if (cmd && !cmd->next && is_builtin(cmd))
		builtin(mini, cmd);
	else
	{
		mini->env_array = env_array(mini);
		while (cmd)
		{
			pipe(fds);
			pid = fork();
			if (pid == 0)
				child_process(mini, cmd, fds);
			else if (pid > 0)
				parent_process(mini, cmd, fds);
			cmd = cmd->next;
		}
		post_exec(mini);
		free_strarray(mini->env_array);
	}
}

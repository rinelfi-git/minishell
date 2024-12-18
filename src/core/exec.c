/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:44:50 by erijania          #+#    #+#             */
/*   Updated: 2024/12/18 19:17:45 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static void	redirect_in_out(t_mini *mini, t_cmd *cmd, int *pipes)
{
	close(pipes[0]);
	if (cmd->fd_in >= 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	else if (cmd->next)
		dup2(pipes[1], 1);
	close(pipes[1]);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		data_free(mini);
		exit(1);
	}
}

static void	fork_builtin(t_mini *mini, t_cmd *cmd, int *pipes)
{
	close(pipes[0]);
	if (cmd->fd_out < 0 && cmd->next)
		cmd->fd_out = pipes[1];
	else
		close(pipes[1]);
	builtin(mini, cmd);
}

static void	child_process(t_mini *mini, t_cmd *cmd, int *pipes)
{
	char	*path;
	int		code;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (is_builtin(cmd))
		fork_builtin(mini, cmd, pipes);
	else if (cmd->args)
	{
		if (get_path(&path, mini->env_list, cmd))
		{
			redirect_in_out(mini, cmd, pipes);
			execve(path, cmd->args, mini->env_array);
		}
		else
			command_not_found(mini, cmd->args[0]);
	}
	if (pipes[0] >= 0)
		close(pipes[0]);
	if (pipes[1] >= 0)
		close(pipes[1]);
	code = mini->exit_code;
	data_free(mini);
	exit(code);
}

static void	parent_process(t_cmd *cmd, int *pipes)
{
	signal(SIGINT, SIG_IGN);
	close(pipes[1]);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->next && cmd->next->fd_in == -2)
		cmd->next->fd_in = pipes[0];
	else
		close(pipes[0]);
}

void	mini_exec(t_mini *mini)
{
	int		fds[2];
	t_cmd	*cmd;
	int		i;

	cmd = mini->cmd;
	if (cmd && !cmd->next && is_builtin(cmd))
		builtin(mini, cmd);
	else
	{
		mini->env_array = env_array(mini);
		mini->pids = malloc(sizeof(pid_t) * cmd_length(cmd));
		i = 0;
		while (cmd)
		{
			pipe(fds);
			mini->pids[i] = fork();
			if (mini->pids[i] == 0)
				child_process(mini, cmd, fds);
			else if (mini->pids[i++] > 0)
				parent_process(cmd, fds);
			cmd = cmd->next;
		}
		post_exec(mini);
	}
}

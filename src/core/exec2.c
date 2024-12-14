/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:40:11 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 15:04:03 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	post_exec(t_mini *mini)
{
	t_cmd	*cmd;
	int		wstatus;

	cmd = mini->cmd;
	while (cmd)
	{
		waitpid(-1, &wstatus, 0);
		if (WIFEXITED(wstatus))
			mini->exit_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			mini->exit_code = 128 + WTERMSIG(wstatus);
			if (mini->exit_code == 131)
				ft_putstr_fd("Quit", 1);
			ft_putchar_fd('\n', 1);
		}
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	main_signal();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:40:11 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 15:08:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static void	code_from_signal(int *status, int *code)
{
	if (WIFEXITED(*status))
		*code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
		{
			*code = 130;
			ft_putchar_fd('\n', 1);
		}
		else if (WTERMSIG(*status) == SIGQUIT)
		{
			*code = 131;
			ft_putendl_fd("Quit", 1);
		}
	}
}

void	post_exec(t_mini *mini)
{
	t_cmd	*cmd;
	int		wstatus;
	int		i;

	cmd = mini->cmd;
	i = 0;
	while (cmd)
	{
		waitpid(mini->pids[i++], &wstatus, 0);
		code_from_signal(&wstatus, &(mini->exit_code));
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	main_signal();
	free(mini->pids);
	free_strarray(mini->env_array);
	mini->env_array = NULL;
	mini->pids = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:40:11 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 09:38:55 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	post_exec(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

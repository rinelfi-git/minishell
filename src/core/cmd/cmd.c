/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:50:46 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 14:46:00 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_cmd(t_mini *mini, t_cmd **last, t_token *token)
{
	t_cmd	*cmd;

	cmd = cmd_append(last);
	cmd->fd_in = get_fdin(mini, token);
	cmd->fd_out = get_fdout(mini, token);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (0);
	cmd->args = get_cmd_params(mini, token);
	return (cmd);
}

int	create_cmd_list(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;

	token = mini->token;
	cmd = 0;
	if (token)
		cmd = create_cmd(mini, &(mini->cmd), token);
	if (!cmd || signal_manager(0, GET_MODE) == SIGINT)
		return (free_lst_cmd(mini));
	token = token->next;
	while (token)
	{
		if (token->prev->type == PIPE)
		{
			cmd = create_cmd(mini, &cmd, token);
			if (!cmd || signal_manager(0, GET_MODE) == SIGINT)
				return (free_lst_cmd(mini));
		}
		token = token->next;
	}
	return (1);
}

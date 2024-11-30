/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:50:46 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 12:23:03 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_cmd(t_cmd **last, t_token *token)
{
	t_cmd	*cmd;
	int		i;

	cmd = cmd_append(last);
	cmd->fd_in = get_fdin(token);
	cmd->fd_out = get_fdout(token);
	cmd->args = get_cmd_params(token);
	printf("fdin %d\n", cmd->fd_in);
	printf("fdout %d\n", cmd->fd_out);
	printf("params\n");
	i = 0;
	while (cmd->args && cmd->args[i])
		printf("[%s]", cmd->args[i++]);
	printf("\n");
	return (cmd);
}

void	create_cmd_list(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;

	token = mini->token;
	cmd = create_cmd(&mini->cmd, token);
	if (cmd)
		token = token->next;
	while (token)
	{
		if (token->prev->type == PIPE)
			cmd = create_cmd(&cmd, token);
		token = token->next;
	}
}
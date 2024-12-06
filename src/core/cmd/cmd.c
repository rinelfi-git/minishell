/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:50:46 by erijania          #+#    #+#             */
/*   Updated: 2024/12/06 23:03:08 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include <stdlib.h>

void	free_lst_cmd(t_mini *mini)
{
	t_cmd	*next;
	t_cmd	*tmp;

	tmp = mini->cmd;
	mini->cmd = 0;
	while (tmp)
	{
		next = tmp->next;
		free_strarray(tmp->args);
		free(tmp);
		tmp = next;
	}
}
/**
 * @brief On ajoute d'abord l'instance de la nouvelle commande à notre liste de commande de la structure principale mini->cmd
 * Un groupe de commande est composé d'un argument, d'un input et d'un output
 * L'output peut varier: soit un fichier soit la sortie standard
 * L'input peut varier: soit un fichier soit l'entré standard
 * Les argumetns sont tous ce qui ne sont pas output/input
 * 
 * @param mini 
 * @param last 
 * @param token 
 * @return t_cmd* 
 */
static t_cmd	*create_cmd(t_mini *mini, t_cmd **last, t_token *token)
{
	t_cmd	*cmd;

	cmd = cmd_append(last);
	cmd->fd_in = get_fdin(mini, token);
	cmd->fd_out = get_fdout(token);
	cmd->args = get_cmd_params(mini, token);
	return (cmd);
}
/**
 * @brief Pour créer une liste de commande avec les arguments et les fichier in et out.
 * à chaque fois qu'on rencontre un PIPE, on crée un groupe de commande
 * 
 * @param mini 
 */
void	create_cmd_list(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;

	token = mini->token;
	cmd = 0;
	if (token)
		cmd = create_cmd(mini, &(mini->cmd), token);
	if (cmd)
		token = token->next;
	while (token)
	{
		if (token->prev->type == PIPE)
			cmd = create_cmd(mini, &cmd, token);
		token = token->next;
	}
}

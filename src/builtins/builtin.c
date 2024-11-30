/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:56:36 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 17:18:26 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#define BUILTIN_LEN 6

int	is_builtin(t_cmd *cmd)
{
	char	*bins[BUILTIN_LEN];
	int		i;

	if (!cmd->args)
		return (0);
	i = 0;
	bins[0] = "cd";
	bins[1] = "echo";
	bins[2] = "env";
	bins[3] = "export";
	bins[4] = "pwd";
	bins[5] = "unset";
	if (!cmd)
		return (0);
	while (i < BUILTIN_LEN)
	{
		if (ft_strncmp(cmd->args[0], bins[i++], INT_MAX) == 0)
			return (1);
	}
	return (0);
}

static int	execute_builtin(t_mini *mini, t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		return (built_env(mini->env));
	return (0);
}

int	builtin(t_mini *mini, t_cmd *cmd)
{
	int	tmp_out;

	if (!is_builtin(cmd))
		return (0);
	if (cmd->fd_out >= 0)
	{
		tmp_out = dup(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
	execute_builtin(mini, cmd);
	if (cmd->fd_out >= 0)
	{
		dup2(tmp_out, STDOUT_FILENO);
		close(tmp_out);
	}
	return (1);
}

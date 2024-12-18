/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:33:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/18 22:01:31 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

char	*get_path(t_env *env, t_cmd *cmd)
{
	char	**paths;
	int		i;

	if (!cmd || !cmd->args[0] || !*(cmd->args[0]))
		return (NULL);
	if (access(cmd->args[0], F_OK) == 0 && access(cmd->args[0], X_OK) == 0)
		cmd->path = ft_strdup(cmd->args[0]);
	if (!ft_getenv(env, "PATH"))
		return (cmd->path);
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	i = 0;
	while (!cmd->path && paths && paths[i])
	{
		cmd->path = ft_strjoin(paths[i++], "/");
		str_append(&(cmd->path), cmd->args[0]);
		if (access(cmd->path, F_OK) != 0 && access(cmd->path, X_OK) != 0)
		{
			free(cmd->path);
			cmd->path = NULL;
		}
	}
	free_strarray(paths);
	return (cmd->path);
}

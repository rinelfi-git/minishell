/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:33:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/16 13:16:06 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

char	*get_path(char **path, t_env *env, t_cmd *cmd)
{
	char	**paths;
	int		i;

	*path = NULL;
	if (!cmd || !cmd->args[0] || !*(cmd->args[0]) || !ft_getenv(env, "PATH"))
		return (*path);
	if (access(cmd->args[0], F_OK) == 0 && access(cmd->args[0], X_OK) == 0)
		cmd->path = ft_strdup(cmd->args[0]);
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	i = 0;
	while (!cmd->path && paths && paths[i])
	{
		*path = ft_strjoin(paths[i++], "/");
		str_append(path, cmd->args[0]);
		if (access(*path, F_OK) == 0 && access(*path, X_OK) == 0)
			cmd->path = *path;
		else
		{
			free(*path);
			*path = NULL;
		}
	}
	free_strarray(paths);
	*path = cmd->path;
	return (*path);
}

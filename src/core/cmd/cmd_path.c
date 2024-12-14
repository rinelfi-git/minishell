/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:33:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 15:21:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "msutils.h"

char	*get_path(t_env *env, t_cmd *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (!cmd || !cmd->args[0] || !*(cmd->args[0]) || !ft_getenv(env, "PATH"))
		return (0);
	if (access(cmd->args[0], F_OK) == 0 && access(cmd->args[0], X_OK) == 0)
		cmd->path = ft_strdup(cmd->args[0]);
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	i = 0;
	while (!cmd->path && paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		str_append(&path, cmd->args[0]);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			cmd->path = path;
		else
			free(path);
	}
	free_strarray(paths);
	return (cmd->path);
}

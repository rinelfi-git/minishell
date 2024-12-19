/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:33:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/19 23:49:57 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static int	null_args(t_cmd *cmd)
{
	return (!cmd || !cmd->args || !cmd->args[0] || !*(cmd->args[0]));
}

static char	*get_absolute(char **paths, char *exe)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (!path && paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		str_append(&path, exe);
		if (access(path, F_OK) != 0 && access(path, X_OK) != 0)
		{
			free(path);
			path = NULL;
		}
	}
	return (path);
}

char	*get_path(t_env *env, t_cmd *cmd)
{
	char	**paths;
	char	*exe;

	cmd->path = NULL;
	if (null_args(cmd) || isdir(cmd->args[0]))
		return (cmd->path);
	exe = cmd->args[0];
	if (access(exe, F_OK) == 0 && access(exe, X_OK) == 0)
		cmd->path = ft_strdup(exe);
	if (env && !ft_getenv(env, "PATH"))
		return (cmd->path);
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	if (!paths)
		return (0);
	cmd->path = get_absolute(paths, exe);
	free_strarray(paths);
	return (cmd->path);
}

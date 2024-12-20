/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:33:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 19:58:02 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static int	null_args(t_cmd *cmd)
{
	return (!cmd || !cmd->args || !cmd->args[0] || !*(cmd->args[0]));
}

static char	*get_relative(char *exe, char **error)
{
	if (isdir(exe))
		*error = ft_strdup(CMD_ERR_DIR);
	else if (access(exe, F_OK) == 0)
	{
		if (access(exe, X_OK) == 0)
			return (ft_strdup(exe));
		else
			*error = ft_strdup(CMD_ERR_PERMISSION);
	}
	else
		*error = ft_strdup(CMD_NOT_FILE);
	return (NULL);
}

static char	*get_absolute(char *env_path, char *exe, char **error)
{
	int		i;
	char	*path;
	char	**path_split;

	i = 0;
	path = NULL;
	path_split = ft_split(env_path, ':');
	if (!path_split)
		return (NULL);
	while (!path && path_split[i])
	{
		path = ft_strjoin(path_split[i++], "/");
		str_append(&path, exe);
		if (access(path, F_OK) != 0 && access(path, X_OK) != 0)
		{
			free(path);
			path = NULL;
		}
	}
	if (!path)
		*error = ft_strdup(CMD_NOT_FOUND);
	free_strarray(path_split);
	return (path);
}

char	*get_path(t_env *env, t_cmd *cmd, char **error)
{
	char	*exe;

	*error = NULL;
	cmd->path = NULL;
	if (null_args(cmd))
		*error = ft_strdup(CMD_NOT_FOUND);
	if (*error)
		return (NULL);
	exe = cmd->args[0];
	if (ft_strchr(exe, '/'))
		cmd->path = get_relative(exe, error);
	else if (env && ft_getenv(env, "PATH"))
		cmd->path = get_absolute(ft_getenv(env, "PATH"), exe, error);
	else
		*error = ft_strdup(CMD_NOT_FILE);
	return (cmd->path);
}

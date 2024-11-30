/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:33:32 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 10:11:45 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "msutils.h"

char	*get_path(t_mini *mini, char *exe)
{
	char	**paths;
	char	*path;
	int		i;

	if (!ft_getenv(mini, "PATH"))
		return (0);
	if (access(exe, F_OK) == 0 && access(exe, X_OK) == 0)
		return (ft_strdup(exe));
	paths = ft_split(ft_getenv(mini, "PATH"), ':');
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		str_append(&path, exe);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (ft_strdup(path));
		free(path);
	}
	free_strarray(paths);
	return (0);
}

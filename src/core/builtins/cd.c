/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:32:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 15:21:01 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

static int	update_vars(t_mini *mini, char *old)
{
	char	*export[4];
	char	cwd[PATH_LEN];

	if (mini->exit_code != 0 || !getcwd(cwd, PATH_LEN))
		return (0);
	export[0] = "export";
	export[1] = ft_strjoin("OLDPWD=", old);
	export[2] = ft_strjoin("PWD=", cwd);
	export[3] = 0;
	built_export(mini, export);
	free(export[1]);
	free(export[2]);
	return (1);
}

static int	access_test(t_mini *mini, char *path)
{
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		mini->exit_code = 1;
		return (0);
	}
	if (!isdir(path))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
		mini->exit_code = 1;
		return (0);
	}
	return (1);
}

int	built_cd(t_mini *mini, char **args)
{
	char	old[PATH_LEN];
	int		len;

	mini->exit_code = 0;
	len = strarraylen(args);
	if (len > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		mini->exit_code = 1;
		return (0);
	}
	if (len == 2 && access_test(mini, args[1]))
	{
		if (!getcwd(old, PATH_LEN))
		{
			ft_bzero(old, PATH_LEN);
			old[0] = '/';
		}
		if (chdir(args[1]))
			ms_perror(ft_strjoin("cd: ", args[1]), &(mini->exit_code));
		return (update_vars(mini, old));
	}
	return (1);
}

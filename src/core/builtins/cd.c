/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:32:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 11:19:46 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"
static void	update_vars(t_mini *mini ,char *old)
{
	char	*export[4];
	char	*cwd;

	cwd = getcwd(0, 0);
	export[0] = "export";
	export[1] = ft_strjoin("OLDPWD=", old);
	export[2] = ft_strjoin("PWD=", cwd);
	export[3] = 0;
	built_export(mini, export);
	free(export[1]);
	free(export[2]);
	free(cwd);
}

static int	access_test(t_mini *mini, char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		mini->exit_code = 1;
		return (0);
	}
	if (!S_ISDIR(stats.st_mode))
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
	char	*old;
	int		len;

	if (strarraylen(args) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		mini->exit_code = 1;
		return (0);
	}
	old = getcwd(0, 0);
	len = strarraylen(args);
	if (len == 1 || (len == 2 && args[1][0] == '~'))
		chdir(ft_getenv(mini->env_list, "HOME"));
	else if (len == 2 && access_test(mini, args[1]))
		chdir(args[1]);
	if (mini->exit_code == 0)
	{
		update_vars(mini, old);
		free(old);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:32:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/04 11:32:42 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"
static void	update_vars(t_env *env ,char *old)
{
	char	*export[4];
	char	*cwd;

	cwd = getcwd(0, 0);
	export[0] = "export";
	export[1] = ft_strjoin("OLDPWD=", old);
	export[2] = ft_strjoin("PWD=", cwd);
	export[3] = 0;
	built_export(env, export);
	free(export[1]);
	free(export[2]);
	free(cwd);
}

int	built_cd(t_env *env, char **args)
{
	char	*old;

	if (len_strarray(args) > 2)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (0);
	}
	old = getcwd(0, 0);
	if (len_strarray(args) == 2)
		chdir(args[1]);
	else
		chdir(ft_getenv(env, "HOME"));
	update_vars(env, old);
	free(old);
	return (1);
}

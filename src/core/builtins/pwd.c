/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:07 by erijania          #+#    #+#             */
/*   Updated: 2024/12/04 12:57:47 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"

int	    built_pwd(t_mini *mini, char **args)
{
	char	*cwd;
	
	if (len_strarray(args) > 1)
	{
		write(STDERR_FILENO, "pwd: too many arguments\n", 24);
		mini->exit_code = 1;
		return (0);
	}
	cwd = getcwd(0, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:07 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 10:57:51 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"

int	    built_pwd(t_mini *mini, char **args)
{
	char	*cwd;
	
	if (strarraylen(args) > 1)
		mini->exit_code = 1;
	cwd = getcwd(0, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (1);
}

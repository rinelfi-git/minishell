/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:07 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 13:50:49 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"

int	    built_pwd(t_mini *mini, char **args)
{
	char	*cwd;
	
	(void)args;
	cwd = getcwd(0, 0);
	printf("%s\n", cwd);
	free(cwd);
	mini->exit_code = 0;
	return (1);
}

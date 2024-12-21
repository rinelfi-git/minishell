/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:07 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 15:47:12 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

int	built_pwd(t_mini *mini)
{
	char	cwd[PATH_LEN];

	if (getcwd(cwd, PATH_LEN) != NULL)
	{
		printf("%s\n", cwd);
		mini->exit_code = 0;
	}
	else
	{
		ms_perror(ft_strdup("pwd"), 0);
		mini->exit_code = ENOENT;
	}
	return (1);
}

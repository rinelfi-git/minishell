/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:12:34 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 12:54:06 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

int	built_exit(t_mini *mini, char **args)
{
	int	cast;
	int	len;

	len = strarraylen(args);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (len == 2)
	{
		if (!isnumber(args[1]))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
			cast = 2;
		}
		else
			cast = ft_atoi(args[1]);
		data_free(mini);
		exit(cast);
	}
	else if(len == 1)
	{
		data_free(mini);
		exit(0);
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		exit(1);
	}
	return (0);
}

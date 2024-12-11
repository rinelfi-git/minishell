/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:12:34 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 13:09:16 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static void	exit_not_numeric(t_mini *mini)
{
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
	mini->exit_code = 2;
}

static void	exit_numeric(t_mini *mini, int exit_code)
{
	data_free(mini);
	exit(exit_code);
}

static void	exit_many_argument(t_mini *mini)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	mini->exit_code = 1;
}

int	built_exit(t_mini *mini, char **args)
{
	int	len;

	len = strarraylen(args);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (len == 2)
	{
		if (!isnumber(args[1]))
			exit_not_numeric(mini);
		else
			exit_numeric(mini, ft_atoi(args[1]));
	}
	else if(len == 1)
		exit_numeric(mini, 0);
	else
		exit_many_argument(mini);
	return (1);
}

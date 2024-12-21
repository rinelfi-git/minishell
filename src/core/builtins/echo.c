/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttelolah <ttelolah@student.42antananavo    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:18 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 09:14:21 by ttelolah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static int	n_argument(char *arg)
{
	if (*(arg++) != '-')
		return (0);
	if (!(*arg) || is_space(*arg))
		return (0);
	while (*arg)
	{
		if (*(arg++) != 'n')
			return (0);
	}
	return (1);
}

int	built_echo(t_mini *mini, char **args)
{
	char	end;
	int		i;

	end = '\n';
	i = 1;
	while (args[i] && n_argument(args[i]))
	{
		end = '\0';
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd(end, 1);
	mini->exit_code = 0;
	return (1);
}

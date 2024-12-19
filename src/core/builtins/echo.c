/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:18 by erijania          #+#    #+#             */
/*   Updated: 2024/12/19 19:16:48 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

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
	if (strarraylen(args) > 1)
	{
		if (n_argument(args[1]))
		{
			end = '\0';
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[++i])
				ft_putchar_fd(' ', 1);
		}
	}
	ft_putchar_fd(end, 1);
	mini->exit_code = 0;
	return (1);
}

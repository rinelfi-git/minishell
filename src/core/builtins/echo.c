/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:18 by erijania          #+#    #+#             */
/*   Updated: 2024/12/16 12:30:28 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

static int	n_argument(char *arg)
{
	if (*(arg++) != '-')
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
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			if (args[++i])
				write(STDOUT_FILENO, " ", 1);
		}
		write(STDOUT_FILENO, &end, 1);
	}
	mini->exit_code = 0;
	return (1);
}

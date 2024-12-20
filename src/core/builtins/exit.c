/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:12:34 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 20:04:16 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"
#include <limits.h>

static void	exit_not_numeric(t_mini *mini)
{
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
	data_free(mini);
	exit(2);
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

static int	exit_atoi(char *str, int *error)
{
	unsigned long long	ret;
	int					sign;
	int					i;
	int					j;

	sign = 1;
	ret = 0;
	i = 0;
	*error = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	j = i;
	while (str[i] && ft_isdigit(str[i]))
		ret = ret * 10 + (str[i++] - '0');
	while (is_space(str[i]))
		i++;
	if (str[i] || i - j > 19 || (sign == -1 && ret - 1 > LONG_MAX)
		|| (sign == 1 && ret > LONG_MAX))
		*error = 1;
	return ((int)(ret * sign) % 256);
}

int	built_exit(t_mini *mini, char **args)
{
	int	len;
	int	code;
	int	error;

	len = strarraylen(args);
	ft_putendl_fd("exit", 1);
	if (len >= 2)
	{
		code = exit_atoi(args[1], &error);
		if (error)
			exit_not_numeric(mini);
		if (len > 2)
			exit_many_argument(mini);
		else
			exit_numeric(mini, (int)code);
	}
	else
		exit_numeric(mini, mini->exit_code);
	return (1);
}

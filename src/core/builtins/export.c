/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:26 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 13:49:18 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static int	is_valid_identifier(char *str)
{
	if (!ft_isalpha(*(str++)))
		return (0);
	while (*str && ft_isalnum(*str))
		str++;
	if (!(*str))
		return (1);
	return (0);
}

static int	has_operation(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

static char	*get_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

static int	do_export(t_mini *mini, char *str)
{
	int		i;
	char	*identifier;

	identifier = get_identifier(str);
	if (!is_valid_identifier(identifier))
		return (export_invalid_identifier(mini, identifier));
	if (!has_operation(str) && !ft_getenv(mini->env_list, str))
		append_env(&(mini->env_list))->name = identifier;
	else
	{
		i = ft_strlen(identifier);
		export_assign(str, i, &(mini->env_list));
		free(identifier);
	}
	mini->exit_code = 0;
	return (1);
}

int	built_export(t_mini *mini, char **args)
{
	int	i;

	if (strarraylen(args) == 1)
		export_print(mini->env_list);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!do_export(mini, args[i++]))
				return (0);
		}
	}
	mini->exit_code = 0;
	return (1);
}

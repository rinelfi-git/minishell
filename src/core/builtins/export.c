/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:26 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 17:51:52 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static int	has_operation(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

static char	*get_export_identifier(char *str)
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
	char	*id;

	id = get_export_identifier(str);
	if (!is_valid_identifier(id))
	{
		free(id);
		return (export_invalid_identifier(mini, str));
	}
	if (!has_operation(str) && !ft_getenv(mini->env_list, id))
		append_env(&(mini->env_list))->name = ft_strdup(id);
	else if (has_operation(str))
	{
		i = ft_strlen(id);
		export_assign(str, i, &(mini->env_list));
	}
	free(id);
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

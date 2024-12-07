/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:06:54 by erijania          #+#    #+#             */
/*   Updated: 2024/12/07 19:40:38 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static char	*get_varname(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '_' || isalpha(str[i]))
		i++;
	while (str[i] && isalnum(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

static int	expand_exitcode(char **str, int i, t_mini *mini)
{
	char	*split[3];

	split[0] = ft_substr(*str, 0, i++);
	split[1] = ft_itoa(mini->exit_code);
	split[2] = ft_substr(*str, i + 1, ft_strlen(*str) - (i + 1));
	expand(mini, split + 2);
	free(*str);
	*str = ft_strjoin(split[0], split[1]);
	str_append(str, split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	return (1);
}

static int	expand_var(char **str, int i, t_mini *mini)
{
	char	*var;
	int		jump;
	char	*split[3];

	split[0] = ft_substr(*str, 0, i++);
	var = get_varname((*str) + i);
	jump = ft_strlen(var);
	if (ft_getenv(mini->env_list, var))
		split[1] = ft_strdup(ft_getenv(mini->env_list, var));
	else
		split[1] = ft_strdup("");
	free(var);
	split[2] = ft_substr(*str, i + jump, ft_strlen(*str) - (i + jump));
	expand(mini, split + 2);
	free(*str);
	*str = ft_strjoin(split[0], split[1]);
	str_append(str, split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	return (1);
}

int	expand(t_mini *mini, char **str)
{
	int		i;

	if (!str)
		return (0);
	if (!(*str))
		return (1);
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1])
		{
			if ((*str)[i + 1] == '?')
				return (expand_exitcode(str, i, mini));
			else
				return (expand_var(str, i, mini));
		}
	}
	return (1);
}

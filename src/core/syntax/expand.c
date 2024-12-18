/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:06:54 by erijania          #+#    #+#             */
/*   Updated: 2024/12/18 18:10:10 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static int	expand_exitcode(t_mini *mini, char **str, int i)
{
	char	**split;

	split = ft_calloc(sizeof(char *), 4);
	if (!split)
		return (MALLOC_ERROR);
	split[0] = ft_substr(*str, 0, i++);
	split[1] = ft_itoa(mini->exit_code);
	split[2] = ft_substr(*str, i + 1, ft_strlen(*str) - (i + 1));
	expand(mini, split + 2);
	free(*str);
	*str = ft_strjoin(split[0], split[1]);
	str_append(str, split[2]);
	free_strarray(split);
	return (1);
}

static int	expand_var(t_mini *mini, char **str, int i)
{
	char	*var;
	int		jump;
	char	**split;

	split = ft_calloc(sizeof(char *), 4);
	if (!split)
		return (0);
	split[0] = ft_substr(*str, 0, i++);
	var = get_identifier((*str) + i);
	jump = ft_strlen(var);
	if (jump == 0)
		split[1] = ft_strdup("$");
	else if (ft_getenv(mini->env_list, var))
		split[1] = ft_strdup(ft_getenv(mini->env_list, var));
	else
		split[1] = ft_strdup("");
	free(var);
	split[2] = ft_substr(*str, i + jump, ft_strlen(*str) - (i + jump));
	expand(mini, split + 2);
	free(*str);
	*str = ft_strjoin(split[0], split[1]);
	str_append(str, split[2]);
	free_strarray(split);
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
				return (expand_exitcode(mini, str, i));
			else
				return (expand_var(mini, str, i));
		}
	}
	return (1);
}

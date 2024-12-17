/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:49:17 by erijania          #+#    #+#             */
/*   Updated: 2024/12/17 20:45:56 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

static int	escape_quote(char **str, int start);

static int	join_escaped_quote(char **str, char *escape, int start)
{
	char	*tmp;

	tmp = ft_substr(*str, 0, start++);
	str_append(&tmp, escape);
	str_append(&tmp, *str + (start++));
	free(*str);
	*str = tmp;
	escape_quote(str, ++start);
	return (1);
}

static int	escape_quote(char **str, int start)
{
	int		i;
	char	q[4];
	
	i = start;
	ft_bzero(q, 4);
	while ((*str)[i])
	{
		if (is_quote((*str)[i]))
		{
			q[1] = (*str)[i];
			if (is_squote(q[1]))
				q[0] = '"';
			else
				q[0] = '\'';
			q[2] = q[0];
			return (join_escaped_quote(str, q, i));
		}
		else
			i++;
	}
	return (1);
}

static int	expand_exitcode(t_mini *mini, char **str, int i)
{
	char	**split;

	split = ft_calloc(sizeof(char *), 4);
	if (!split)
		return (MALLOC_ERROR);
	split[0] = ft_substr(*str, 0, i++);
	split[1] = ft_itoa(mini->exit_code);
	split[2] = ft_substr(*str, i + 1, ft_strlen(*str) - (i + 1));
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
	escape_quote(split + 1, 0);
	split[2] = ft_substr(*str, i + jump, ft_strlen(*str) - (i + jump));
	free(*str);
	*str = ft_strjoin(split[0], split[1]);
	str_append(str, split[2]);
	free_strarray(split);
	return (1);
}

int	expand_first(t_mini *mini, char **in, int start)
{
	char	*str;

	if (!in)
		return (0);
	if (!(*in))
		return (1);
	str = *in;
	if (str[start + 1] == '?')
		return (expand_exitcode(mini, in, start));
	return (expand_var(mini, in, start));
}

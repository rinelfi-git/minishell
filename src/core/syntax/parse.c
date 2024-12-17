/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:53:38 by erijania          #+#    #+#             */
/*   Updated: 2024/12/16 12:51:03 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

static int	sequence_count(char *str)
{
	char	quote;

	quote = 0;
	if (!str || !*str)
		return (0);
	if (is_quote(*str))
	{
		quote = *(str++);
		while (*str && *str != quote)
			str++;
		if (*str)
			str++;
		return (1 + sequence_count(str));
	}
	while (*str && !is_quote(*str))
		str++;
	return (1 + sequence_count(str));
}

static char	*split_quoted(t_mini *mini, char *str, int *i, int use_expand)
{
	int		j;
	char	quote;
	char	*split;

	if (!str || !is_quote(*str))
		return (0);
	quote = *str;
	j = 1;
	split = 0;
	while (str[j] && str[j] != quote)
		j++;
	split = ft_substr(str, 1, j - 1);
	j++;
	if (quote == '"' && use_expand)
		expand(mini, &split);
	(*i) += j;
	return (split);
}

static char	*split_literral(t_mini *mini, char *str, int *i, int use_expand)
{
	int		j;
	char	*split;

	if (!str)
		return (0);
	j = 0;
	split = 0;
	while (str[j] && !is_quote(str[j]))
		j++;
	if (j > 0 && is_quote(str[j]) && str[j - 1] == '$')
		split = ft_substr(str, 0, j - 1);
	else
		split = ft_substr(str, 0, j);
	if (use_expand)
		expand(mini, &split);
	(*i) += j;
	return (split);
}

static char	*parse_split(t_mini *mini, char *str, int *i, int use_expand)
{
	if (is_quote(*str))
		return (split_quoted(mini, str, i, use_expand));
	return (split_literral(mini, str, i, use_expand));
}

int	parse(t_mini *mini, char **str, int use_expand)
{
	char	**split;
	int		jump;
	int		i;

	if (!(*str))
		return (1);
	split = malloc(sizeof(char *) * (sequence_count(*str) + 1));
	if (!split)
		return (0);
	i = 0;
	jump = 0;
	while ((*str)[jump])
		split[i++] = parse_split(mini, (*str) + jump, &jump, use_expand);
	split[i] = 0;
	free(*str);
	*str = 0;
	i = 0;
	while (split[i])
		str_append(str, split[i++]);
	free_strarray(split);
	return (1);
}

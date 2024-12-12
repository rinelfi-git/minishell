/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:53:38 by erijania          #+#    #+#             */
/*   Updated: 2024/12/12 14:57:14 by erijania         ###   ########.fr       */
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

static char	*parse_split(t_mini *mini, char *str, int *i)
{
	int		j;
	char	quote;
	char	*substr;
	
	j = 0;
	substr = 0;
	if (is_quote(str[j]))
	{
		quote = str[j++];
		while (str[j] && str[j] != quote)
			j++;
		substr = ft_substr(str, 1, j - 1);
		j++;
		if (quote == '"')
			expand(mini, &substr);
	}
	else
	{
		while (str[j] && !is_quote(str[j]))
			j++;
		substr = ft_substr(str, 0, j);
		expand(mini, &substr);
	}
	(*i) += j;
	return (substr);
}

int	parse(t_mini *mini, char **str)
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
		split[i++] = parse_split(mini, (*str) + jump, &jump);
	split[i] = 0;
	free(*str);
	*str = 0;
	i = 0;
	while (split[i])
		str_append(str, split[i++]);
	free_strarray(split);
	return (1);
}

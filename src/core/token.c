/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:39:10 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 13:38:18 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"
#include <stdlib.h>

void	free_lst_token(t_mini *mini)
{
	t_token	*next;
	t_token	*tmp;

	tmp = mini->token;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = next;
	}
	mini->token = 0;
}

static int	command_length(char *line)
{
	int		i;
	char	open;

	i = 0;
	while (line[i] && !is_space(line[i]) && !is_special(line + i))
	{
		if (is_quote(line[i]))
		{
			open = line[i++];
			while (line[i] && line[i] != open)
				i++;
			if (line[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

static int	add_cmd(t_token **head, char **line)
{
	int		length;
	char	*str;

	length = command_length(*line);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (0);
	str = ft_substr(*line, 0, length);
	token_append(head, str, ARG);
	(*head)->type = CMD;
	(*line) += length;
	return (1);
}

static void	add_special(t_token **head, char **line)
{
	int	spec;

	spec = is_special(*line);
	if (spec == INPUT)
		token_append(head, ft_strdup("<"), INPUT);
	else if (spec == PIPE)
		token_append(head, ft_strdup("|"), PIPE);
	else if (spec == HEREDOC)
		token_append(head, ft_strdup("<<"), HEREDOC);
	else if (spec == TRUNC)
		token_append(head, ft_strdup(">"), TRUNC);
	else if (spec == APPEND)
		token_append(head, ft_strdup(">>"), APPEND);
	if (spec == INPUT || spec == PIPE || spec == TRUNC)
		(*line)++;
	else if (spec == HEREDOC || spec == APPEND)
		(*line) += 2;
}

void	create_token_list(t_token **head, char *line)
{
	*head = 0;
	while (is_space(*line))
		line++;
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (is_special(line))
			add_special(head, &line);
		else
			add_cmd(head, &line);
	}
}

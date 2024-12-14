/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:39:10 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 14:46:01 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

int	free_lst_token(t_token **head)
{
	t_token	*next;

	if (!head)
		return (-1);
	if (!(*head))
		return (0);
	next = (*head)->next;
	free((*head)->str);
	free(*head);
	*head = 0;
	return (free_lst_token(&next));
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
	str = ft_substr(*line, 0, length);
	token_append(head, str, ARG);
	if ((*head)->type == ARG)
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
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (*line && is_special(line))
			add_special(head, &line);
		else if (*line)
			add_cmd(head, &line);
	}
}

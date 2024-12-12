/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:29:12 by erijania          #+#    #+#             */
/*   Updated: 2024/12/12 21:26:38 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msutils.h"
#include "libft.h"

static int	closed_quote(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			quote = *(str++);
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				quote = 0;
		}
		str++;
	}
	if (quote)
		return (0);
	return (1);
}

static int	unexpected_token(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (0);
}

int	syntax_ok(char *str)
{
	t_token	*token;
	t_token	*tmp;
	int		special;

	create_token_list(&token, str);
	tmp = token;
	if (tmp)
		add_history(str);
	while (tmp)
	{
		if (!closed_quote(tmp->str))
			return (unclosed_quote());
		if (tmp->type == PIPE && (!tmp->next || tmp->next->type != CMD))
			return (unexpected_token("|"));
		special = INPUT;
		while (special <= APPEND)
			if (tmp->type == special++ && (!tmp->next || tmp->next->type != ARG))
				return (unexpected_token(tmp->str));
		tmp = tmp->next;
	}
	free_lst_token(&token);
	return (1);
}

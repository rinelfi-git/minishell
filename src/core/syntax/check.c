/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:29:12 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 14:43:08 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msutils.h"
#include "libft.h"

static int	closed_quote(char *str)
{
	char	quote;

	quote = 0;
	printf("Check %s\n", str);
	while (*str)
	{
		if (is_quote(*str))
		{
			quote = *(str++);
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				quote = 0;
			if (*str)
				str++;
		}
		else
			str++;
	}
	if (quote)
		return (0);
	return (1);
}

static int	unexpected_token(int *code, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	*code = 2;
	return (0);
}

static void	post_check(int valid, char *in)
{
	if (!valid)
		free(in);
}

int	syntax_ok(char *str, int *code)
{
	t_token	*token;
	t_token	*tmp;
	int		special;
	int		ok;

	create_token_list(&token, str);
	ok = 1;
	tmp = token;
	if (tmp && tmp->type == PIPE)
		ok = unexpected_token(code, "|");
	while (ok && tmp)
	{
		if (!closed_quote(tmp->str))
			ok = unclosed_quote(code);
		if (ok && tmp->type == PIPE && !tmp->next)
			ok = unexpected_token(code, "|");
		special = INPUT;
		while (ok && special <= APPEND)
			if (tmp->type == special++ && !tmp->next)
				ok = unexpected_token(code, "newline");
		tmp = tmp->next;
	}
	free_lst_token(&token);
	post_check(ok, str);
	return (ok);
}

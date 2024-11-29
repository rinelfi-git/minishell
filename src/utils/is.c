/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:41:43 by erijania          #+#    #+#             */
/*   Updated: 2024/11/29 13:30:03 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_space(char c)
{
	return (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f'
			|| c == '\t' || c == '\v'));
}

int	is_special(char *str)
{
	size_t	len;

	if (!str || !(*str))
		return (0);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			return (HEREDOC);
		if (ft_strncmp(str, ">>", 2) == 0)
			return (APPEND);
	}
	if (len >= 1)
	{
		if (*str == '<')
			return (INPUT);
		if (*str == '>')
			return (TRUNC);
		if (*str == '|')
			return (PIPE);
	}
	return (0);
}

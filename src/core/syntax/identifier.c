/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:55:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 16:12:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_valid_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (!(*str));
}

char	*get_identifier(char *str)
{
	int	i;

	if (!str)
		return (ft_strdup(""));
	if (ft_isdigit(str[0]))
		return (ft_substr(str, 0, 1));
	i = 1;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (!i)
		return (ft_strdup(""));
	return (ft_substr(str, 0, i));
}

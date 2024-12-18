/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:55:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/18 18:11:09 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && (ft_isalnum(*str) || *str != '_'))
		str++;
	if (!(*str))
		return (1);
	return (0);
}

char	*get_identifier(char *str)
{
	int	i;

	if (!str)
		return (ft_strdup(""));
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (!i)
		return (ft_strdup(""));
	return (ft_substr(str, 0, i));
}

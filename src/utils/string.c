/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:51:25 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 16:26:11 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <sys/types.h>

void	str_append(char **dest, char *src)
{
	char	*tmp;
	size_t	length;

	if (!dest || !src)
		return ;
	if (!(*dest))
		*dest = ft_strdup("");
	length = ft_strlen(*dest) + ft_strlen(src) + 1;
	tmp = malloc(sizeof(char) * length);
	ft_bzero(tmp, length);
	if (!tmp)
		return ;
	ft_strlcat(tmp, *dest, length);
	ft_strlcat(tmp, src, length);
	free(*dest);
	*dest = tmp;
}

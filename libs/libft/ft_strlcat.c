/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:09:41 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 20:19:11 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(dst);
	if (size <= (size_t)len)
		return (size + ft_strlen(src));
	return (len + ft_strlcpy(dst + len, src, size - len));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:44:18 by erijania          #+#    #+#             */
/*   Updated: 2024/02/24 17:21:15 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int			i;

	if (!dest && !src)
		return (NULL);
	if (src >= dest)
		ft_memcpy(dest, src, n);
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			((unsigned char *)dest)[i] = ((unsigned const char *)src)[i];
			i--;
		}
	}
	return (dest);
}

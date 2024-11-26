/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:51:06 by erijania          #+#    #+#             */
/*   Updated: 2024/02/24 17:08:57 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0)
	{
		if (*((unsigned char *)s1) != *((unsigned char *)s2))
			return (*((unsigned char *)s1) - *(unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

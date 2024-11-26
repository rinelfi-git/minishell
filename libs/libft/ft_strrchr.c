/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:39 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 21:36:48 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	while (i-- > 0)
	{
		if (((unsigned char)s[i]) == ((unsigned char)c))
			return ((char *)(s + i));
	}
	return (NULL);
}

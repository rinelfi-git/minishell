/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:38:10 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 18:39:34 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t n1, size_t n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = ft_min(ft_strlen(s1) + 1, ft_strlen(s2) + 1);
	return (ft_memcmp(s1, s2, ft_min(n, len)));
}

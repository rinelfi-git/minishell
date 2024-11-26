/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:01:03 by erijania          #+#    #+#             */
/*   Updated: 2024/02/24 22:57:05 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

static int	ft_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;

	if ((long)len < 0)
		len = ft_max(0, ft_strlen(haystack) + 1 + len);
	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *) haystack);
	while (*haystack && len >= n_len)
	{
		if (ft_strncmp(haystack, needle, ft_min(len, n_len)) == 0)
			return ((char *) haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

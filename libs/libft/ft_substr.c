/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:13:58 by erijania          #+#    #+#             */
/*   Updated: 2024/02/24 20:42:22 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_min(size_t s1, size_t s2)
{
	if (s1 < s2)
		return (s1);
	return (s2);
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		is_empty;
	size_t	s_len;

	is_empty = 0;
	s_len = ft_strlen(s);
	if (start >= s_len || len == 0)
		is_empty = 1;
	if (is_empty)
		len = 1;
	else
		len = ft_min(ft_abs(s_len - start), len) + 1;
	ret = (char *)malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	if (is_empty)
		ret[0] = '\0';
	else
		ft_strlcpy(ret, s + start, len);
	return (ret);
}

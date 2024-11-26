/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:40 by erijania          #+#    #+#             */
/*   Updated: 2024/02/26 08:20:14 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*ret;
	size_t	length;

	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *end))
		end--;
	length = (end - start) + 2;
	ret = (char *)malloc(length * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, start, length);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:50:57 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 20:16:28 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;

	len = ft_strlen(s) + 1;
	ret = malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, (char *) s, len);
	return (ret);
}

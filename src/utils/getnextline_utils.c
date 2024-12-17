/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttelolah <ttelolah@student.42antananavo    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:56:49 by ttelolah          #+#    #+#             */
/*   Updated: 2024/12/17 08:56:52 by ttelolah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t gnl_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void *gnl_memcpy(void *dst, const void *src, size_t n)
{
    size_t i;

    i = 0;
    if (!dst && !src)
        return (NULL);
    while (i < n)
    {
        ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
        i++;
    }
    return (dst);
}

char *gnl_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (*s == (char)c)
        return ((char *)s);
    return (NULL);
}

char *gnl_strjoin(char *s1, char *s2)
{
    char    *str;
    size_t  len1;
    size_t  len2;

    if (!s1 || !s2)
        return (NULL);
    len1 = gnl_strlen(s1);
    len2 = gnl_strlen(s2);
    str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!str)
        return (NULL);
    gnl_memcpy(str, s1, len1);
    gnl_memcpy(str + len1, s2, len2);
    str[len1 + len2] = '\0';
    return (str);
}
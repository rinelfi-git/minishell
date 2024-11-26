/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:11:19 by erijania          #+#    #+#             */
/*   Updated: 2024/02/24 21:22:19 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	**memclear(char **tab, size_t max)
{
	size_t	j;

	j = max;
	while (j > 0)
	{
		j--;
		if (tab[j])
		{
			free(tab[j]);
			tab[j] = NULL;
		}
	}
	free(tab);
	tab = NULL;
	return (tab);
}

static char	**get_string(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (*s)
	{
		size = 0;
		while (*s && *s == c)
			s++;
		while (s[size] && s[size] != c)
			size++;
		if (size > 0)
		{
			tab[i] = ft_substr(s, 0, size);
			if (!tab[i])
				return (memclear(tab, i + 1));
			i++;
		}
		s += size;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	size;

	size = count_words(s, c);
	ret = (char **)ft_calloc(size + 1, sizeof(char **));
	if (ret == NULL)
		return (NULL);
	return (get_string(ret, s, c));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:06:24 by erijania          #+#    #+#             */
/*   Updated: 2024/12/17 16:12:06 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	get_line_length(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*tmp;
	int		length;

	if (!*stash)
		return (NULL);
	length = get_line_length(*stash);
	line = (char *)malloc(sizeof(char) * (length + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, *stash, length);
	line[length] = '\0';
	if ((*stash)[length])
	{
		tmp = ft_strdup((*stash) + length);
		free(*stash);
		*stash = tmp;
	}
	else
	{
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

static char	*read_file(int fd, char **stash)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*stash, buffer);
		free(*stash);
		*stash = temp;
	}
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!read_file(fd, &stash))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (extract_line(&stash));
}

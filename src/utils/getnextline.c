#include "minishell.h"

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
	char	*temp;
	int		i;

	if (!*stash)
		return (NULL);
	i = get_line_length(*stash);
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	gnl_memcpy(line, *stash, i);
	line[i] = '\0';
	if ((*stash)[i])
	{
		temp = gnl_strjoin((*stash) + i, "");
		free(*stash);
		*stash = temp;
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
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = gnl_strjoin(*stash, buffer);
		free(*stash);
		*stash = temp;
	}
	free(buffer);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = gnl_strjoin("", "");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:15:24 by erijania          #+#    #+#             */
/*   Updated: 2024/12/02 16:04:15 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static void	read_process(t_doc *doc, int *pp)
{
	char	*line;

	line = 0;
	while (1)
	{
		line = readline("document> ");
		if (!line)
		{
			free(line);
			break ;
		}
		if (ft_strncmp(doc->delimiter, line, INT_MAX) == 0)
			break ;
		str_append(&line, "\n");
		write(pp[1], line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
}

static void	heredoc(t_doc *doc)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		read_process(doc, fd);
		close(fd[1]);
		exit(0);
	}
	wait(0);
	close(fd[1]);
	doc->fd = fd[0];
}

int	open_heredoc(char *delimiter)
{
	t_doc	doc;
	char	qt;
	int		i;

	doc.escape = 1;
	doc.fd = -2;
	doc.delimiter = delimiter;
	i = -1;
	while (doc.escape && delimiter[++i])
	{
		if (is_quote(delimiter[i]))
		{
			qt = delimiter[i];
			while (delimiter[++i] != qt)
				;
			if (delimiter[i])
				doc.escape = 0;
		}
	}
	heredoc(&doc);
	return (doc.fd);
}

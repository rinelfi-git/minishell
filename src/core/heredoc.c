/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:15:24 by erijania          #+#    #+#             */
/*   Updated: 2024/12/07 19:42:21 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static void	read_process(t_mini *mini, t_doc *doc, int *pp)
{
	char	*line;
	char	*invite;
	int		line_count;

	line = 0;
	invite = ft_strjoin("<", doc->delimiter);
	str_append(&invite, "> ");
	while (1)
	{
		line = readline(invite);
		if (!line)
		{
			heredoc_eof(doc->delimiter, line_count);
			free(line);
			break ;
		}
		if (ft_strncmp(doc->delimiter, line, INT_MAX) == 0)
			break ;
		line_count++;
		if (doc->expand)
			expand(mini, &line);
		ft_putendl_fd(line, pp[1]);
		free(line);
	}
	free(invite);
}

static void	heredoc(t_mini *mini, t_doc *doc)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		read_process(mini, doc, fd);
		close(fd[1]);
		exit(0);
	}
	wait(0);
	close(fd[1]);
	doc->fd = fd[0];
}

int	open_heredoc(t_mini *mini, char *delimiter)
{
	t_doc	doc;
	char	quote;
	int		i;

	doc.expand = 1;
	doc.fd = -2;
	doc.delimiter = ft_strdup(delimiter);
	i = -1;
	while (doc.expand && delimiter[++i])
	{
		if (is_quote(delimiter[i]))
		{
			quote = delimiter[i];
			while (delimiter[++i] != quote)
				;
			if (delimiter[i])
				doc.expand = 0;
		}
	}
	parse(mini, &(doc.delimiter));
	heredoc(mini, &doc);
	free(doc.delimiter);
	return (doc.fd);
}

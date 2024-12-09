/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:15:24 by erijania          #+#    #+#             */
/*   Updated: 2024/12/09 13:45:41 by erijania         ###   ########.fr       */
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
	line_count = 0;
	invite = ft_strjoin("<", doc->delimiter);
	str_append(&invite, "> ");
	while (1)
	{
		line = readline(invite);
		printf("INPUT [%s]\n", line);
		if (!line)
		{
			heredoc_eof(doc->delimiter, line_count);
			free(line);
			break ;
		}
		if (ft_strncmp(doc->delimiter, line, INT_MAX) == 0)
			break ;
		if (doc->expand)
			expand(mini, &line);
		ft_putendl_fd(line, pp[1]);
		line_count++;
		free(line);
	}
	free(invite);
}

static void	heredoc(t_mini *mini, t_doc *doc)
{
	int		fd[2];
	pid_t	pid;
	int		wstatus;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_signal();
		read_process(mini, doc, fd);
		close(fd[1]);
		exit(0);
	}
	else
		prevent_signal();
	wait(&wstatus);
	close(fd[1]);
	main_signal();
	if (WIFEXITED(wstatus))
	{
		printf("EXIT %d\n", WEXITSTATUS(wstatus));
		signal_manager(SIGINT, SET_MODE);
	}
	if (signal_manager(0, GET_MODE) == SIGINT)
		doc->fd = -2;
	else
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

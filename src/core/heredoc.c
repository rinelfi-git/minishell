/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:15:24 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 15:18:09 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static int	heredoc_quit(t_mini *mini, t_doc *heredoc, int fd_in, int code)
{
	if (fd_in >= 0)
		close (fd_in);
	free(heredoc->delimiter);
	data_free(mini);
	return (code);
}

static void	read_process(t_mini *mini, t_doc *doc, int fd_in)
{
	char	*line;
	int		line_count;

	line_count = 0;
	while (1)
	{
		line = readline(HD_PROMPT);
		if (!line)
		{
			if (signal_manager(0, GET_MODE) == SIGINT)
				exit(heredoc_quit(mini, doc, fd_in, 130));
			heredoc_eof(doc, line_count);
			break ;
		}
		if (ft_strncmp(doc->delimiter, line, INT_MAX) == 0)
			break ;
		if (doc->expand)
			expand(mini, &line);
		ft_putendl_fd(line, fd_in);
		free(line);
		line_count++;
	}
	exit(heredoc_quit(mini, doc, fd_in, 0));
}

static void	heredoc(t_mini *mini, t_doc *doc)
{
	int		fds[2];
	pid_t	pid;
	int		wstatus;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		heredoc_signal();
		close(fds[0]);
		read_process(mini, doc, fds[1]);
	}
	else
	{
		close(fds[1]);
		signal(SIGINT, SIG_IGN);
	}
	wait(&wstatus);
	main_signal();
	if (WIFEXITED(wstatus))
		mini->exit_code = WEXITSTATUS(wstatus);
	if (mini->exit_code == 130 && signal_manager(SIGINT, SET_MODE) == SIGINT)
		close(fds[0]);
	else
		doc->fd = fds[0];
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
	parse(mini, &(doc.delimiter), 0);
	heredoc(mini, &doc);
	free(doc.delimiter);
	return (doc.fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/20 20:12:23 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

static char	*get_input(t_mini *mini)
{
	char	*in;
	int		code;

	in = readline(MAIN_PROMPT);
	if (!in)
	{
		code = mini->exit_code;
		data_free(mini);
		exit(code);
	}
	return (in);
}

static int	preexpand(t_mini *mini, char **in)
{
	int		i;
	char	*ref;

	i = 0;
	ref = *in;
	while (ref[i] && is_space(ref[i]))
		i++;
	if (ref[i] == '$')
		expand_first(mini, in, i);
	return (1);
}

static int	save_history(char *line)
{
	int		i;
	int		fd;
	char	*line_with_newline;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i])
	{
		add_history(line);
		fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (0);
		line_with_newline = ft_strjoin(line, "\n");
		if (!line_with_newline)
		{
			close(fd);
			return (0);
		}
		write(fd, line_with_newline, ft_strlen(line_with_newline));
		free(line_with_newline);
		close(fd);
	}
	return (1);
}

static void	load_history(void)
{
	int		fd;
	char	*line;

	fd = open(HISTORY_FILE, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	prompt(t_mini *mini)
{
	char	*in;

	main_signal();
	load_history();
	while (1)
	{
		in = get_input(mini);
		if (signal_manager(0, GET_MODE) == SIGINT)
			mini->exit_code = 130;
		signal_manager(0, SET_MODE);
		save_history(in);
		preexpand(mini, &in);
		if (!syntax_ok(in, &(mini->exit_code)))
			continue ;
		create_token_list(&(mini->token), in);
		free(in);
		create_cmd_list(mini);
		if (mini->cmd)
			mini_exec(mini);
		free_lst_token(&(mini->token));
		free_lst_cmd(mini);
	}
}

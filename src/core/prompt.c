/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/16 15:18:53 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static char	*get_input()
{
	char	*in;

	in = readline("~$ ");
	if (!in)
		in = ft_strdup("exit 0");
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
		expand(mini, in);
	return (1);
}

static int	save_history(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i])
		add_history(line);
	return (1);
}

void	prompt(t_mini *mini)
{
	char	*in;

	main_signal();
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		in = get_input();
		if (signal_manager(0, GET_MODE) == SIGINT)
			mini->exit_code = 130;
		signal_manager(0, SET_MODE);
		save_history(in);
		preexpand(mini, &in);
		if (!syntax_ok(in, &(mini->exit_code)))
			continue ;
		create_token_list(&(mini->token), in);
		create_cmd_list(mini);
		if (mini->cmd)
			mini_exec(mini);
		free_lst_token(&(mini->token));
		free_lst_cmd(mini);
		free(in);
	}
}

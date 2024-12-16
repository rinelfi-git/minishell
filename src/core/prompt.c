/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/15 23:05:16 by erijania         ###   ########.fr       */
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

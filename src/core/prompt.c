/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 14:45:58 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static void	prompt_path(char **out, char *user)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(0, 0);
	if (cwd)
	{
		tmp = ft_strjoin("/home/", user);
		if (ft_strncmp(tmp, cwd, ft_strlen(tmp)) == 0)
		{
			str_append(out, TERM_SECONDARY"~");
			str_append(out, cwd + ft_strlen(tmp));
		}
		else
		{
			str_append(out, TERM_SECONDARY);
			str_append(out, cwd);
		}
		free(tmp);
	}
	free(cwd);
}

static char	*get_prompt(t_mini *mini)
{
	char	*user;
	char	*out;

	user = ft_getenv(mini->env_list, "USER");
	out = ft_strjoin(TERM_PRIMARY, user);
	str_append(&out, "@minishell"TERM_DEFAULT"["TERM_SECONDARY);
	prompt_path(&out, user);
	str_append(&out, TERM_DEFAULT"]$ ");
	return (out);
}

static char	*get_input(t_mini *mini)
{
	char	*in;
	char	*prompt;

	prompt = get_prompt(mini);
	in = readline(prompt);
	if (!in)
		in = ft_strdup("exit 0");
	free(prompt);
	return (in);
}

void	prompt(t_mini *mini)
{
	char	*in;

	main_signal();
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		in = get_input(mini);
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

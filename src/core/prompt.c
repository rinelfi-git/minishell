/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 13:57:41 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static char	*get_prompt(t_mini *mini)
{
	char	*user;
	char	path[PATH_LEN];
	char	*temp;
	char	*out;

	user = ft_getenv(mini, "USER");
	out = ft_strjoin(TERM_PRIMARY, user);
	str_append(&out, "@minishell"TERM_DEFAULT"["TERM_SECONDARY);
	if (getcwd(path, PATH_LEN))
	{
		temp = ft_strjoin("/home/", user);
		if (ft_strncmp(temp, path, ft_strlen(temp)) == 0)
		{
			str_append(&out, TERM_SECONDARY"~");
			str_append(&out, path + ft_strlen(temp));
		}
		else
		{
			str_append(&out, TERM_SECONDARY);
			str_append(&out, path);
		}
		free(temp);
	}
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
	{
		free(in);
		in = 0;
	}
	free(prompt);
	return (in);
}

void	prompt(t_mini *mini)
{
	char	*in;

	while (1)
	{
		in = get_input(mini);
		if (!in)
			break ;
		add_history(in);
		create_token_list(&(mini->token), in);
		create_cmd_list(mini);
		mini_exec(mini);
		free_lst_cmd(mini);
		free_lst_token(mini);
		free(in);
	}
}

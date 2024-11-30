/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 08:23:26 by erijania         ###   ########.fr       */
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

	user = ft_getenv("USER", mini);
	out = ft_strjoin("\033[0;32m", user);
	str_append(&out, "@minishell\033[0m:");
	if (getcwd(path, PATH_LEN))
	{
		temp = ft_strjoin("/home/", user);
		if (ft_strncmp(temp, path, ft_strlen(temp)) == 0)
		{
			str_append(&out, "\033[34m~");
			str_append(&out, path + ft_strlen(temp));
		}
		else
		{
			str_append(&out, "\033[34m");
			str_append(&out, path);
		}
		free(temp);
	}
	str_append(&out, "\033[0m $ ");
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
	t_token	*loop;

	while (1)
	{
		in = get_input(mini);
		if (!in)
			break ;
		create_token_list(&(mini->token), in);
		loop = mini->token;
		while (loop)
		{
			printf("[%s]\n", loop->str);
			loop = loop->next;
		}
		add_history(in);
		free(in);
	}
}

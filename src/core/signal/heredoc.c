/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:03:19 by erijania          #+#    #+#             */
/*   Updated: 2024/12/09 17:27:52 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	sigint(int signal)
{
	signal_manager(signal, SET_MODE);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDIN_FILENO);
	exit(130);
}

void	heredoc_signal(void)
{
	signal(SIGINT, sigint);
}

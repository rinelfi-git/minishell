/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:03:19 by erijania          #+#    #+#             */
/*   Updated: 2024/12/19 22:48:54 by erijania         ###   ########.fr       */
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
	close(0);
}

void	heredoc_signal(void)
{
	signal(SIGINT, sigint);
}

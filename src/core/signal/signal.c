/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:45:52 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 12:12:02 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	signal_manager(int signal, int mode)
{
	static int	signal_storage = 0;

	if (mode == SET_MODE)
	{
		signal_storage = signal;
		return (signal);
	}
	else if (mode == GET_MODE)
		return (signal_storage);
	return (-2);
}

static void	sigint(int signal)
{
	signal_manager(signal, SET_MODE);
	ft_putstr_fd("\n", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_redisplay();
}

void	main_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
}

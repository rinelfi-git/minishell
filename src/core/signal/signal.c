/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:45:52 by erijania          #+#    #+#             */
/*   Updated: 2024/12/09 14:35:39 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	signal_manager(int signal, int mode)
{
	static pid_t	signal_storage = 0;
	
	if (mode == SET_MODE)
		signal_storage = signal;
	else if (mode == GET_MODE)
		return (signal_storage);
	return (-2);
}
static void	sigint(int signal)
{
	signal_manager(signal, SET_MODE);
	ioctl(STDIN_FILENO, TIOCSTI, "\0");
}

static void	prevent_sigint(int signal)
{
	(void)signal;
}

void	main_signal(void)
{
	signal(SIGINT, sigint);
}
void	prevent_signal(void)
{
	signal(SIGINT, prevent_sigint);
}

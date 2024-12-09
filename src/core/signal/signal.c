/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:45:52 by erijania          #+#    #+#             */
/*   Updated: 2024/12/09 11:50:44 by erijania         ###   ########.fr       */
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
void	sigint(int signal)
{
	signal_manager(signal, SET_MODE);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\r\n", STDIN_FILENO);
	rl_redisplay();
}

void	main_signal(void)
{
	signal(SIGINT, sigint);
}

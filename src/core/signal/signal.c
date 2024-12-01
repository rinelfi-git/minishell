/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:45:52 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 19:14:34 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>

int	pid_signal_manager(pid_t pid, int mode)
{
	static pid_t	pid_storage = 0;
	
	if (mode == SET_MODE)
		pid_storage = pid;
	else if (mode == GET_MODE)
		return (pid_storage);
	return (-2);
}

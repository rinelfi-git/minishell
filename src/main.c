/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:28:30 by erijania          #+#    #+#             */
/*   Updated: 2024/11/26 09:55:03 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini	minishell;

	(void)ac;
	(void)av;
	minishell_init(&minishell);
	minishell_env(&minishell, env);
	return (0);
}
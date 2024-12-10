/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:28:30 by erijania          #+#    #+#             */
/*   Updated: 2024/12/10 21:05:04 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief On initialise la structure du programme
 * On assigne juste des valeurs par défauts pour les attributs,
 * On initialise le tout à 0 (0 entier, 0 pour un pointeur NULL, 0 si un caractère '\0')
 * après l'initialisation on récupère la variable d'environnement dans la liste chainée
 * mini->env_list
 * une fois l'initialisation faite, on affiche le prompt
 * 
 * @param ac 
 * @param av 
 * @param env 
 * @return int 
 */
int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	data_init(&mini);
	data_env(&mini, env);
	prompt(&mini);
	data_free(&mini);
	return (mini.exit_code);
}

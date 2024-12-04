/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:53:38 by erijania          #+#    #+#             */
/*   Updated: 2024/12/04 12:50:08 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_mini *mini, char **str)
{
	// existence double/simple quote
	// si simple quote ne pas expander les variables qui se trouvent dans la chaine
	// ex: une chaine qui contient 'une $HOME' => une chaine qui contient une $HOME
	// si double quote expander les variables qui se trouvent dans la chaine
	// ex: une chaine qui contient "une $HOME" et exit "$?" => une chaine qui contient une /home/user et exit 0
	// l'expansion utilise la fonction expand(t_mini, char **)
	return (1);
}

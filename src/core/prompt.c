/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:44:32 by erijania          #+#    #+#             */
/*   Updated: 2024/12/04 11:29:29 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msutils.h"

static void	prompt_path(char **out, char *user)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(0, 0);
	if (cwd)
	{
		tmp = ft_strjoin("/home/", user);
		if (ft_strncmp(tmp, cwd, ft_strlen(tmp)) == 0)
		{
			str_append(out, TERM_SECONDARY"~");
			str_append(out, cwd + ft_strlen(tmp));
		}
		else
		{
			str_append(out, TERM_SECONDARY);
			str_append(out, cwd);
		}
		free(tmp);
	}
	free(cwd);
}

/**
 * @brief Récupère les infoirmations à afficher dans le prompt
 * notament, le nom d'utilisateur de la session,
 * le dossier où le shell est lancé
 * 
 * @param mini 
 * @return char* 
 */
static char	*get_prompt(t_mini *mini)
{
	char	*user;
	char	*out;

	user = ft_getenv(mini->env_list, "USER");
	out = ft_strjoin(TERM_PRIMARY, user);
	str_append(&out, "@minishell"TERM_DEFAULT"["TERM_SECONDARY);
	prompt_path(&out, user);
	str_append(&out, TERM_DEFAULT"]$ ");
	return (out);
}
/**
 * @brief Permet de formater le prompt récupérer l'input utilisateur depuis l'entré standard
 * 
 * @param mini 
 * @return char* 
 */
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

/**
 * @brief À chaque boucle, on récupère la valeur de l'entré standard avec readline.
 * ensuite, on ajoute la saisie à l'historique de commande.
 * On crée une liste de token quon sauvegardera dans la structure principale du programme
 * qui est mini->token
 * Une fois la tokenisation terminée on les transforme en une ligne de commande
 * qu'on pourra exécuter dans la boucle d'exécution
 * On exécute la liste de commande puis on libère les tokens et commandes précédement
 * créés pour faire place à le nouvelle ligne de commande saisie
 * 
 * @param mini 
 */
void	prompt(t_mini *mini)
{
	char	*in;

	while (1)
	{
		in = get_input(mini);
		if (!in)
			break ;
		add_history(in);
		create_token_list(&(mini->token), in);
		create_cmd_list(mini);
		mini_exec(mini);
		free_lst_token(mini);
		free_lst_cmd(mini);
		free(in);
	}
}

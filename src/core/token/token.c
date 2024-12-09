/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:39:10 by erijania          #+#    #+#             */
/*   Updated: 2024/12/09 20:38:25 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

int	free_lst_token(t_mini *mini)
{
	t_token	*next;
	t_token	*tmp;

	tmp = mini->token;
	mini->token = 0;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->str);
		tmp->str = 0;
		free(tmp);
		tmp = next;
	}
	return (0);
}
/**
 * @brief Tant qu'on n'a pas trouvé une espace ou un caractère spécial,
 * on prend le caractère suivant comme faisant partie du groupe de caractère actuel.
 * Pour le cas d'un double/simple guillemet, on parcours la chaine jusqu'à ce qu'on trouve sa fermeture
 * 
 * @param line 
 * @return int 
 */
static int	command_length(char *line)
{
	int		i;
	char	open;

	i = 0;
	while (line[i] && !is_space(line[i]) && !is_special(line + i))
	{
		if (is_quote(line[i]))
		{
			open = line[i++];
			while (line[i] && line[i] != open)
				i++;
			if (line[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}
/**
 * @brief On ajoute le groupe de chaine avec le type argument ou commande ou argument
 * Par défaut, tous les tokens sont de type argument, mais si ce bout de chaîne se trouve en tête de liste
 * c'est frocement une commande. Le reste est est toujours argument
 * Comme, dans l'ajout des caractères spéciaux, on saute sur la prochaîne groupe de caractère, une fois l'ajout terminé.
 * 
 * @param head 
 * @param line 
 * @return int 
 */
static int	add_cmd(t_token **head, char **line)
{
	int		length;
	char	*str;

	length = command_length(*line);
	str = ft_substr(*line, 0, length);
	token_append(head, str, ARG);
	if ((*head)->type == ARG)
		(*head)->type = CMD;
	(*line) += length;
	return (1);
}
/**
 * @brief Ajoute le groupe de caractère spécial en bien spécifiant son type.
 * Une fois l'ajout terminé, on décide de déplacer le pointeur de la chaîne de l'entré pour interpréter la chaîne suivante
 * 
 * @param head 
 * @param line 
 */
static void	add_special(t_token **head, char **line)
{
	int	spec;

	spec = is_special(*line);
	if (spec == INPUT)
		token_append(head, ft_strdup("<"), INPUT);
	else if (spec == PIPE)
		token_append(head, ft_strdup("|"), PIPE);
	else if (spec == HEREDOC)
		token_append(head, ft_strdup("<<"), HEREDOC);
	else if (spec == TRUNC)
		token_append(head, ft_strdup(">"), TRUNC);
	else if (spec == APPEND)
		token_append(head, ft_strdup(">>"), APPEND);
	if (spec == INPUT || spec == PIPE || spec == TRUNC)
		(*line)++;
	else if (spec == HEREDOC || spec == APPEND)
		(*line) += 2;
}
/**
 * @brief Crée une liste de token, en commençant par éliminer toutes els espaces
 * Si c'est un ou groupe de caractère(s) spécial(aux) : (<, >, |, <<, >>) On l'ajoute en tant que token
 * ayant un type slécial (Voir le header minishell.h pour trouver la liste de tous les types de token)
 * Si c'est un simple groupe de caractère on l'ajoute en tant que commande
 * Il faut toujours vérifier qu'on est pas arrivé au bout de la chaîne
 * 
 * @param head 
 * @param line 
 */
void	create_token_list(t_token **head, char *line)
{
	*head = 0;
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (*line && is_special(line))
			add_special(head, &line);
		else if (*line)
			add_cmd(head, &line);
	}
}

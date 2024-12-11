/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:54:34 by erijania          #+#    #+#             */
/*   Updated: 2024/12/11 10:04:13 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env(t_env **head, t_env *env)
{
	t_env	*tmp;

	if (!head || !env)
		return (0);
	tmp = *head;
	if (env == tmp)
	{
		*head = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	else
		return (delete_env(&(tmp->next), env));
}

int	free_lst_env(t_mini *mini)
{
	while (mini->env_list)
		delete_env(&(mini->env_list), mini->env_list);
	return (0);
}

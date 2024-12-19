/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:54:34 by erijania          #+#    #+#             */
/*   Updated: 2024/12/19 16:43:20 by erijania         ###   ########.fr       */
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

int	env_list_length(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

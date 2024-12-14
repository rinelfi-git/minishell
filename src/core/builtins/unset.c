/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:33:37 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 15:36:33 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	remove_env_variable(t_env **env_list, char *var_name)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	built_unset(t_mini *mini, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_variable(&mini->env_list, args[i]);
		i++;
	}
	mini->exit_code = 0;
	return (0);
}

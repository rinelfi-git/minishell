/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:33:01 by erijania          #+#    #+#             */
/*   Updated: 2024/12/19 17:04:05 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msutils.h"
#include "libft.h"

static int	create_env(t_env **head, char *var)
{
	int		limits[2];
	char	*name;
	char	*value;
	t_env	**last_env;

	limits[0] = 0;
	while (var[limits[0]] && var[limits[0]] != '=')
		limits[0]++;
	name = ft_substr(var, 0, limits[0]);
	limits[1] = ++limits[0];
	while (var[limits[1]])
		limits[1]++;
	value = ft_substr(var, limits[0], limits[1]);
	last_env = head;
	while (*last_env)
		last_env = &((*last_env)->next);
	*last_env = ft_calloc(sizeof(t_env), 1);
	if (!(*last_env))
		return (MALLOC_ERROR);
	(*last_env)->name = name;
	(*last_env)->value = value;
	(*last_env)->next = 0;
	return (0);
}

void	data_init(t_mini *mini)
{
	mini->exit_code = 0;
	mini->env_list = NULL;
	mini->env_array = NULL;
	mini->token = NULL;
	mini->cmd = NULL;
	mini->pids = NULL;
}

int	data_free(t_mini *mini)
{
	free_lst_token(&(mini->token));
	free_lst_cmd(mini);
	free_lst_env(mini);
	if (mini->env_array)
		free_strarray(mini->env_array);
	if (mini->pids)
		free(mini->pids);
	data_init(mini);
	return (mini->exit_code);
}

void	data_env(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (create_env(&(mini->env_list), env[i++]) < 0)
		{
			data_free(mini);
			exit(EXIT_FAILURE);
		}
	}
}

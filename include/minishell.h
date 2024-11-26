/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:59 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_minishell	t_mini;
typedef struct s_env		t_env;

struct s_minishell
{
	int		ret;
	t_env	*env;
};

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
};
#endif
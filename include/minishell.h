/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/11/28 16:29:29 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# define PATH_LEN	1024

# define CMD		1
# define ARG		2
# define PIPE		3
# define INPUT		4
# define HEREDOC	5
# define TRUNC		6
# define APPEND		7

typedef struct s_minishell	t_mini;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
struct s_minishell
{
	int		ret;
	t_env	*env;
	t_token	*token;
};

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
};

struct s_token
{
	char	*str;
	int		type;
	int		expand;
	t_token	*next;
};

void	minishell_init(t_mini *mini);
void	minishell_env(t_mini *mini, char **env);
void	prompt(t_mini *mini);
char	*ft_getenv(char *var, t_mini *mini);
void	token_append(t_token **head, char *str, int type);
void	create_token_list(t_token **head, char *line);
#endif
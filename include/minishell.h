/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 10:35:48 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# define PATH_LEN		1024

# define TERM_PRIMARY	"\033[0m\033[1;91m"
# define TERM_SECONDARY	"\033[0m\033[92m"
# define TERM_DEFAULT	"\033[0m"

# define CMD			1
# define ARG			2
# define PIPE			3
# define INPUT			4
# define HEREDOC		5
# define TRUNC			6
# define APPEND			7

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

void	data_init(t_mini *mini);
void	data_env(t_mini *mini, char **env);
void	prompt(t_mini *mini);
char	*ft_getenv(t_mini *mini, char *var);
void	token_append(t_token **head, char *str, int type);
void	create_token_list(t_token **head, char *line);
char	*get_path(t_mini *mini, char *exe);
void    built_env(t_mini *mini);
#endif
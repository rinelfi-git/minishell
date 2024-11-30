/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/11/30 12:17:04 by erijania         ###   ########.fr       */
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
typedef struct s_cmd		t_cmd;
struct s_minishell
{
	int		ret;
	t_env	*env;
	t_token	*token;
	t_cmd	*cmd;
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
	t_token	*prev;
	t_token	*next;
};

struct s_cmd
{
	char	**args;
	int		fd_in;
	int		fd_out;
	t_cmd	*next;
	t_cmd	*prev;
};


void	data_init(t_mini *mini);
void	data_env(t_mini *mini, char **env);
void	prompt(t_mini *mini);
char	*ft_getenv(t_mini *mini, char *var);
void	create_token_list(t_token **head, char *line);
t_token	*token_append(t_token **head, char *str, int type);
void	create_cmd_list(t_mini *mini);
t_cmd	*cmd_append(t_cmd **head);
char	**get_cmd_params(t_token *token);
char	*get_path(t_mini *mini, char *exe);
int		get_fdin(t_token *token);
int		get_fdout(t_token *token);
void    built_env(t_mini *mini);
#endif
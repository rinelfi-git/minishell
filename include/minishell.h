/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/12/04 12:45:32 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
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

# define SET_MODE		1
# define GET_MODE		2

typedef struct s_minishell	t_mini;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_doc		t_doc;
typedef struct s_cmd		t_cmd;
struct s_minishell
{
	int		exit_code;
	t_env	*env_list;
	char	**env_array;
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
	t_token	*prev;
	t_token	*next;
};

struct s_cmd
{
	char	*path;
	char	**args;
	int		fd_in;
	int		fd_out;
	t_cmd	*next;
	t_cmd	*prev;
};

struct s_doc
{
	char	*delimiter;
	int		expand;
	int		fd;
};


int		pid_signal_manager(pid_t pid, int mode);
void	data_init(t_mini *mini);
void	data_env(t_mini *mini, char **env);
void	data_free(t_mini *mini);
void	prompt(t_mini *mini);
int		expand(t_mini *mini, char **str);
int		parse(char **str);

char	*ft_getenv(t_env *env, char *var);
char	**env_array(t_mini *mini);
t_env	*append_env(t_env **head);
t_env	*env_get(t_env **head, char *name);

void	create_token_list(t_token **head, char *line);
t_token	*token_append(t_token **head, char *str, int type);
void	create_cmd_list(t_mini *mini);
t_cmd	*cmd_append(t_cmd **head);
char	**get_cmd_params(t_token *token);
int		cmd_length(t_cmd *head);
char	*get_path(t_env *env, t_cmd *cmd);
int		get_fdin(t_mini *mini, t_token *token);
int		get_fdout(t_token *token);

int		is_builtin(t_cmd *cmd);
int		builtin(t_mini *mini, t_cmd *cmd);
int	    built_env(t_env *env);
int		built_cd(t_env *env, char **args);
int	    built_export(t_env *env, char **args);
int	    built_echo(t_env *env);
int	    built_pwd(t_env *env);
int	    built_unset(t_env *env);

void	mini_exec(t_mini *mini);
void	free_lst_cmd(t_mini *mini);
void	free_lst_token(t_mini *mini);
int		open_heredoc(t_mini *mini, char *delimiter);
void	wait_all(t_cmd *cmd);
#endif
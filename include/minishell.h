/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/12/15 12:32:29 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <errno.h>

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

# define MALLOC_ERROR	-1

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

int		signal_manager(int signal, int mode);
void	data_init(t_mini *mini);
void	data_env(t_mini *mini, char **env);
int		data_free(t_mini *mini);
void	prompt(t_mini *mini);
int		expand(t_mini *mini, char **str);
int		parse(t_mini *mini, char **str, int use_expand);
int		syntax_ok(char *str, int *code);

char	*ft_getenv(t_env *env, char *var);
char	**env_array(t_mini *mini);
t_env	*append_env(t_env **head);
t_env	*env_get(t_env **head, char *name);
int		delete_env(t_env **head, t_env *env);
int		free_lst_env(t_mini *mini);

void	create_token_list(t_token **head, char *line);
t_token	*token_append(t_token **head, char *str, int type);
int		create_cmd_list(t_mini *mini);
t_cmd	*cmd_append(t_cmd **head);
char	**get_cmd_params(t_mini *mini, t_token *token);
int		cmd_length(t_cmd *head);
char	*get_path(t_env *env, t_cmd *cmd);
int		get_fdin(t_mini *mini, t_token *token);
int		get_fdout(t_mini *mini, t_token *token);

int		is_builtin(t_cmd *cmd);
int		builtin(t_mini *mini, t_cmd *cmd);
int		built_env(t_mini *mini);
int		built_cd(t_mini *mini, char **args);
int		built_export(t_mini *mini, char **args);
int		built_echo(t_mini *mini, char **args);
int		built_pwd(t_mini *mini, char **args);
int		built_unset(t_mini *mini, char **args);
int		built_exit(t_mini *mini, char **args);
int		export_append(char *str, int i, t_env **env);
int		export_assign(char *str, int i, t_env **env);
void	export_print(t_env *env);

void	mini_exec(t_mini *mini);
int		free_lst_cmd(t_mini *mini);
int		free_lst_token(t_token **head);
int		open_heredoc(t_mini *mini, char *delimiter);
void	post_exec(t_mini *mini);

void	main_signal(void);
void	heredoc_signal(void);
#endif
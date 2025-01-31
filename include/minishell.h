/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:53:21 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 15:49:37 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH_LEN 1024

# define MAIN_PROMPT "minishell:~$ "
# define HD_PROMPT "> "
# define HISTORY_FILE "/tmp/minishell"

# define CMD 1
# define ARG 2
# define PIPE 3
# define INPUT 4
# define HEREDOC 5
# define TRUNC 6
# define APPEND 7

# define SET_MODE 1
# define GET_MODE 2

# define MALLOC_ERROR -1
# define CMD_ERR_DIR ": Is a directory"
# define CMD_NOT_FILE ": No such file or directory"
# define CMD_NOT_FOUND ": command not found"
# define CMD_NOT_FOUND_DOT ": filename argument required"
# define CMD_ERR_PERMISSION ": Permission denied"

typedef struct s_minishell	t_mini;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_doc		t_doc;
typedef struct s_cmd		t_cmd;
struct						s_minishell
{
	int		exit_code;
	t_env	*env_list;
	char	**env_array;
	t_token	*token;
	t_cmd	*cmd;
	pid_t	*pids;
};

struct						s_env
{
	char					*name;
	char					*value;
	t_env					*next;
};

struct						s_token
{
	char					*str;
	int						type;
	t_token					*prev;
	t_token					*next;
};

struct						s_cmd
{
	char					*path;
	char					**args;
	int						fd_in;
	int						fd_out;
	t_cmd					*next;
	t_cmd					*prev;
};

struct						s_doc
{
	char					*delimiter;
	int						expand;
	int						fd;
};

int							signal_manager(int signal, int mode);
void						data_init(t_mini *mini);
void						data_env(t_mini *mini, char **env);
int							data_free(t_mini *mini);
void						prompt(t_mini *mini);

char						*ft_getenv(t_env *env, char *var);
char						**env_array(t_mini *mini);
t_env						*append_env(t_env **head);
t_env						*env_get(t_env **head, char *name);
int							delete_env(t_env **head, t_env *env);
int							free_lst_env(t_mini *mini);
int							env_list_length(t_env *env);

char						*get_identifier(char *str);
int							is_valid_identifier(char *str);
int							syntax_ok(char *str, int *code);
int							expand_first(t_mini *mini, char **in, int start);
int							escape_special(char **out, int type, int start);
int							escape_quote(char **str, int start);
int							expand(t_mini *mini, char **str);
int							parse(t_mini *mini, char **str, int use_expand);

void						create_token_list(t_token **head, char *line);
t_token						*token_append(t_token **head, char *str, int type);
int							create_cmd_list(t_mini *mini);
t_cmd						*cmd_append(t_cmd **head);
char						**get_cmd_params(t_mini *mini, t_token *token);
int							cmd_length(t_cmd *head);
char						*get_path(t_env *env, t_cmd *cmd, char **error);
int							get_fdin(t_mini *mini, t_token *token);
int							get_fdout(t_mini *mini, t_token *token);

int							is_builtin(t_cmd *cmd);
int							builtin(t_mini *mini, t_cmd *cmd);
int							built_env(t_mini *mini);
int							built_cd(t_mini *mini, char **args);
int							built_export(t_mini *mini, char **args);
int							built_echo(t_mini *mini, char **args);
int							built_pwd(t_mini *mini);
int							built_unset(t_mini *mini, char **args);
int							built_exit(t_mini *mini, char **args);
int							export_assign(char *str, int i, t_env **env);
void						export_print(t_env *env);

void						mini_exec(t_mini *mini);
int							free_lst_cmd(t_mini *mini);
int							free_lst_token(t_token **head);
int							open_heredoc(t_mini *mini, char *delimiter);
void						post_exec(t_mini *mini);

void						main_signal(void);
void						heredoc_signal(void);
#endif
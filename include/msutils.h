/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:52:26 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 14:46:04 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSUTILS_H
# define MSUTILS_H
# include "minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

void		str_append(char **dest, char *src);
int			is_space(char c);
int			is_special(char *str);
int			is_dquote(char c);
int			is_squote(char c);
int			is_quote(char c);
int			isdir(char *path);
int			isnumber(char *str);
void		free_strarray(char **array);
int			strarraylen(char **array);
void		command_error(t_mini *mini, char *str, char *error);
void		heredoc_eof(t_doc *heredoc, int line);
void		ms_perror(char *path, int *code);
int			export_invalid_identifier(t_mini *mini, char *id);
int			unclosed_quote(int *code);
char		*get_next_line(int fd);
#endif
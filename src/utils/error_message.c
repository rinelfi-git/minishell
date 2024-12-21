/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:31:56 by erijania          #+#    #+#             */
/*   Updated: 2024/12/21 13:20:49 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msutils.h"

void	command_error(t_mini *mini, char *str, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
	if (ft_strncmp(error, CMD_ERR_DIR, INT_MAX) == 0 ||
		ft_strncmp(error, CMD_ERR_PERMISSION, INT_MAX) == 0 ||
		ft_strncmp(error, CMD_NOT_FILE, INT_MAX) == 0)
		mini->exit_code = 126;
	else if (ft_strncmp(error, CMD_NOT_FOUND, INT_MAX) == 0)
		mini->exit_code = 127;
	free(error);
}

void	heredoc_eof(t_doc *heredoc, int line)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(heredoc->delimiter, 2);
	ft_putendl_fd("')", 2);
}

void	ms_perror(char *path)
{
	char	*msg;

	msg = ft_strjoin("minishell: ", path);
	perror(msg);
	free(msg);
}

int	export_invalid_identifier(t_mini *mini, char *id)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(id, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	mini->exit_code = 1;
	return (0);
}

int	unclosed_quote(int *code)
{
	ft_putendl_fd("minishell: syntax error: unexpected EOF", 2);
	*code = 2;
	return (0);
}

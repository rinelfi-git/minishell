/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:31:56 by erijania          #+#    #+#             */
/*   Updated: 2024/12/12 21:05:50 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	command_not_found(t_mini *mini, char *str)
{
	if (ft_strchr(str, '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	mini->exit_code = 127;
}

void	heredoc_eof(char *delimiter, int line)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	fd_error(char *path)
{
	char	*msg;

	msg = ft_strjoin("minishell: ", path);
	perror(msg);
	free(msg);
}
int	export_invalid_identifier(t_mini *mini, char *id)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	free(id);
	mini->exit_code = 1;
	return (0);
}

int	unclosed_quote(void)
{
	ft_putendl_fd("minishell: syntax error: unexpected EOF", STDERR_FILENO);
	return (0);
}

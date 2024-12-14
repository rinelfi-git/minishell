/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:31:56 by erijania          #+#    #+#             */
/*   Updated: 2024/12/14 15:22:39 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	command_not_found(t_mini *mini, char *str)
{
	if (ft_strchr(str, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': command not found", 2);
	}
	mini->exit_code = 127;
}

void	heredoc_eof(char *delimiter, int line)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
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
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(id, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(id);
	mini->exit_code = 1;
	return (0);
}

int	unclosed_quote(int *code)
{
	ft_putendl_fd("minishell: syntax error: unexpected EOF", 2);
	*code = 2;
	return (0);
}

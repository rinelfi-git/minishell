/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:14:32 by erijania          #+#    #+#             */
/*   Updated: 2024/11/28 15:15:58 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_dquote(char c)
{
	return (c == '"');
}

int	is_squote(char c)
{
	return (c == '\'');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

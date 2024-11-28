/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:52:26 by erijania          #+#    #+#             */
/*   Updated: 2024/11/28 15:16:13 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSUTILS_H
# define MSUTILS_H

void	str_append(char **dest, char *src);
int		is_space(char c);
int		is_special(char *str);
int		is_dquote(char c);
int		is_squote(char c);
int		is_quote(char c);
#endif
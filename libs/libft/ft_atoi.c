/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:10:30 by erijania          #+#    #+#             */
/*   Updated: 2024/07/08 10:32:34 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long	ft_atoi(const char *nptr)
{
	long	ret;
	int		sign;

	sign = 1;
	ret = 0;
	while (ft_isblank(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
		ret = ret * 10 + ((long) *(nptr++) - '0');
	return (ret * sign);
}

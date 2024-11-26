/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 07:44:27 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 20:57:02 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static int	n_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int	n_length(int n)
{
	int	ret;

	ret = 1;
	if (n < 0)
		ret++;
	n = n * n_sign(n);
	while (n / 10)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		length;
	int		sign;
	char	*ret;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	sign = n_sign(n);
	length = n_length(n);
	n = n * sign;
	ret = (char *)malloc((length + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[length--] = '\0';
	while ((sign > 0 && length >= 0) || (sign < 0 && length > 0))
	{
		ret[length--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign < 0)
		ret[length] = '-';
	return (ret);
}

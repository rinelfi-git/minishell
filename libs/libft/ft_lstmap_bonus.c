/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:41:35 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 12:32:44 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;

	if (!lst || !f)
		return (NULL);
	ret = ft_lstnew(f(lst->content));
	if (!ret)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	if (lst->next)
		ret->next = ft_lstmap(lst->next, f, del);
	return (ret);
}

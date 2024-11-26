/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:55:47 by erijania          #+#    #+#             */
/*   Updated: 2024/02/25 14:23:28 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*heap;

	if (!lst || !del)
		return ;
	heap = *lst;
	if (heap && heap->next)
		ft_lstclear(&heap->next, del);
	ft_lstdelone(heap, del);
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:50:32 by sna               #+#    #+#             */
/*   Updated: 2021/03/13 16:02:29 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*link;

	if (lst == 0 || del == 0)
		return ;
	while (*lst != NULL)
	{
		link = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = link;
	}
	*lst = NULL;
}
/*
** Deletes and frees the given element and every successor of that element,
** using the function 'del' and free(3).
** Finally, the pointer to the list must be set to NULL.
*/

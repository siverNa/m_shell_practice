/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:05:05 by sna               #+#    #+#             */
/*   Updated: 2021/03/13 15:49:09 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
** Counts the number of elements in a list.
** Return value is Length of the list.
** If 'next' contains the following node address, it means,
** 'lst->next' contains 'next address'.
** Therefore, lst = lst->next == lst = 'next address'
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:10:33 by sna               #+#    #+#             */
/*   Updated: 2021/01/05 18:13:17 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_l;

	new_l = malloc(sizeof(t_list));
	if (new_l == 0)
		return (0);
	new_l->content = content;
	new_l->next = NULL;
	return (new_l);
}
/*
** Allocates (with malloc(3)) and returns a new element.
** The variable 'content' is initialized with
** the value of the parameter 'content'.
** The variable 'next' is initialized to NULL.
*/

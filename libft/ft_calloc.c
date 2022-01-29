/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:45:04 by sna               #+#    #+#             */
/*   Updated: 2020/12/27 19:01:35 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c_nmemb;

	c_nmemb = (void *)malloc(nmemb * size);
	if (c_nmemb == 0)
		return (0);
	ft_memset(c_nmemb, 0, nmemb * size);
	return (c_nmemb);
}
/*
** There is the number of array elements, 'nmemb',
** and the size of each array element, 'size'.
** Allocate memory by 'nmemb' * 'size'
** and initialize allocated memory to zero(0).
** The return value is the pointer to the allocated memory.
*/

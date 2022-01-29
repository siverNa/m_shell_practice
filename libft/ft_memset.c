/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:58:23 by sna               #+#    #+#             */
/*   Updated: 2020/12/25 17:42:49 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
** ft_memset() is write 'n' byte of value 'c', in 's'
** s : Start pointer to the memory you want to populate (start address)
** c : The value that you want to fill in memory. It is int-type,
** but is internally converted to unsigned char (1 byte) and stored.
** n : The number of bytes that you want to fill,
** that is, the amount of memory you want to fill.
*/

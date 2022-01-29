/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:02:49 by sna               #+#    #+#             */
/*   Updated: 2021/01/05 21:49:11 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;
	size_t			i;

	if (dest == 0 && src == 0)
		return (NULL);
	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	i = 0;
	if (c_dest > c_src)
	{
		while (++i <= n)
			c_dest[n - i] = c_src[n - i];
	}
	else
	{
		while (n-- > 0)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	}
	return (dest);
}
/*
** Copy 'n' byte from 'src' memory to 'dest' memory.
** The 'src' array first copies the memory area
** that does not overlap the memory area of 'src' and 'dest'.
** Returns the pointer in the dest.
*/

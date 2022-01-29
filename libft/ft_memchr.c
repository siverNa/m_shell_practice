/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:27:38 by sna               #+#    #+#             */
/*   Updated: 2020/12/26 20:38:47 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*u_s;

	u_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (u_s[i] == (unsigned char)c)
			return (u_s + i);
		i++;
	}
	return (0);
}
/*
** It is similar to a string manipulation function strchr().
** Find a specific character 'c' in the memory of 's' within 'n',
** and return the location.
** If not found, returns null.
*/

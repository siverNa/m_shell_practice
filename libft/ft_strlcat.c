/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:05:12 by sna               #+#    #+#             */
/*   Updated: 2020/12/23 22:06:46 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	result;
	int		i;
	int		j;

	dst_len = ft_strlen(dst);
	result = ft_strlen(src);
	i = 0;
	j = dst_len;
	while ((src[i] != '\0') && dst_len + 1 + i < size)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	if (size < dst_len)
		result = result + size;
	else
		result = result + dst_len;
	return (result);
}
/*
** ft_strlcat() is Add 'src' to the end of 'dst' by 'size - strlen(dst) - 1',
** and Insert a NULL character at the end.
** Size contains one NULL digit.
** The 'size' is the 'size of the destination buffer'
** and the return value depends on the 'size' and 'dst size'.
** size < dst (line 33 ~ 34), return strlen(src) + size,
** size > dst (line 35 ~ 36O, return strlen(src) + strlen(dst).
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:22:38 by sna               #+#    #+#             */
/*   Updated: 2020/12/23 18:19:25 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	src_len = ft_strlen(src);
	while (i < src_len && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (src_len);
}
/*
** strlcpy() takes the full size of the destination buffe
** and copies up to 'dstsize - 1' characters from the string 'src' to 'dst'
** NUL-terminating the result if dstsize is not 0.
** return value is 'the length of src'
** if dst, src value is null, retrun 0
*/

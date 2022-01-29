/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:31:37 by sna               #+#    #+#             */
/*   Updated: 2021/01/05 18:49:20 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*c_s;

	if (s == 0)
		return (0);
	c_s = (char *)malloc(sizeof(char) * (len + 1));
	if (c_s == 0)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	while (i < len && i + start < s_len)
	{
		c_s[i] = s[start + i];
		i++;
	}
	c_s[i] = '\0';
	return (c_s);
}
/*
** Allocates (with malloc(3)) and returns a substring from the string 's'
** The substring begins at index 'start' and is of maximum size 'len'.
** If successful, return the partial string
** if 's' is empty or allocation fails, return NULL.
*/

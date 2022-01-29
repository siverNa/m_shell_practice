/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:26:49 by sna               #+#    #+#             */
/*   Updated: 2021/01/06 18:42:46 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_s;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_s = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (join_s == 0)
		return (0);
	ft_memcpy(join_s, s1, s1_len);
	ft_memcpy(join_s + s1_len, s2, s2_len);
	join_s[s1_len + s2_len] = 0;
	return (join_s);
}
/*
** Allocates (with malloc(3)) and returns a new string,
** which is the result of the concatenation of 's1' and 's2'.
** If successful, 's1' + 's2' returns combined memory.
** If unsuccessful, return NULL.
*/

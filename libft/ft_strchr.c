/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:18:01 by sna               #+#    #+#             */
/*   Updated: 2021/03/13 14:20:56 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c && c == 0)
		return ((char *)s + i);
	return (0);
}
/*
** The strchr() function returns a pointer to the first character 'c'
** found in the string 's'.
** If c is not found, it returns null.
** If 's' or 'c' was not entered, return null.
*/

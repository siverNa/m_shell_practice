/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:25:01 by sna               #+#    #+#             */
/*   Updated: 2021/01/05 18:39:33 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	end;
	char	*result;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	front = 0;
	end = ft_strlen(s1);
	while (s1[front] != '\0' && ft_strchr(set, s1[front]))
		front++;
	while (s1[end - 1] != '\0' && ft_strchr(set, s1[end - 1]))
	{
		if (end - 1 < 1)
			break ;
		end--;
	}
	if (front > end)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (end - front + 1));
	if (result == 0)
		return (0);
	ft_strlcpy(result, s1 + front, end - front + 1);
	return (result);
}
/*
** Allocates (with malloc()) and returns a copy of 's1' with the characters
** specified in 'set' removed from the beginning and the end of the string.
** If successful, return the manipulated 's1'.
** Returns NULL if failed or failed to allocate.
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:13:41 by sna               #+#    #+#             */
/*   Updated: 2021/01/09 15:56:32 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*temp;
	size_t	i;

	len = ft_strlen(s);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
/*
** Assign the string 's' length + 1 size as 'malloc()'
** and copy the string 's' and return it.
** Since 'malloc()' processed data is returned,
** the returned memory must be released via free().
** That is, 'strdup' equals 'malloc' + 'strcpy'.
** Returns the copied string address if the string is replicated normally,
** or returns NULL if it fails.
*/

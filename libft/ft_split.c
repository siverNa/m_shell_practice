/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:45:37 by sna               #+#    #+#             */
/*   Updated: 2021/03/13 14:31:32 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_cnt(char const *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

char	**ft_free(char **new_str)
{
	size_t	i;

	i = 0;
	while (new_str[i])
	{
		free(new_str[i]);
		i++;
	}
	free(new_str);
	return (NULL);
}

char	*ft_s_to_new(char *n_str, char const *s, size_t a_i, size_t str_len)
{
	size_t	i;

	i = 0;
	while (str_len > 0)
	{
		n_str[i] = s[a_i - str_len];
		i++;
		str_len--;
	}
	n_str[i] = '\0';
	return (n_str);
}

char	**ft_split_sec(char **new_str, char const *s, char c, size_t count_str)
{
	size_t	a_i;
	size_t	m_i;
	size_t	str_len;

	a_i = 0;
	m_i = 0;
	str_len = 0;
	while (s[a_i] != '\0' && m_i < count_str)
	{
		while (s[a_i] != '\0' && s[a_i] == c)
			a_i++;
		while (s[a_i] != '\0' && s[a_i] != c)
		{
			a_i++;
			str_len++;
		}
		new_str[m_i] = (char *)malloc(sizeof(char) * (str_len + 1));
		if (new_str[m_i] == NULL)
			return (ft_free(new_str));
		ft_s_to_new(new_str[m_i], s, a_i, str_len);
		str_len = 0;
		m_i++;
	}
	new_str[m_i] = 0;
	return (new_str);
}

char	**ft_split(char const *s, char c)
{
	char	**new_str;
	size_t	count_str;

	if (s == 0)
		return (NULL);
	count_str = ft_get_cnt(s, c);
	new_str = (char **)malloc(sizeof(char *) * (count_str + 1));
	if (new_str == NULL)
		return (NULL);
	ft_split_sec(new_str, s, c, count_str);
	return (new_str);
}
/*
** Allocates (with malloc(3)) and returns an array of strings
** obtained by splitting 's' using the character 'c' as a delimiter.
** The array must be ended by a NULL pointer.
** The array of new strings resulting from the split.
** NULL if the allocation fails.
*/

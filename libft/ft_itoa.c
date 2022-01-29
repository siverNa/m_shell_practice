/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:42:29 by sna               #+#    #+#             */
/*   Updated: 2021/03/13 16:21:39 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	determin(int n)
{
	long long	temp;

	if (n < 0)
		temp = -(long long)n;
	else
		temp = (long long)n;
	return ((long long)temp);
}

int	get_len_int(int n)
{
	int			len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			s_len;
	int			check;
	char		*str;
	long long	temp;

	if (n < 0)
		check = -1;
	else
		check = 1;
	s_len = get_len_int(n);
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (str == 0)
		return (NULL);
	str[s_len] = 0;
	s_len--;
	temp = determin(n);
	while (s_len >= 0)
	{
		str[s_len] = temp % 10 + '0';
		temp = temp / 10;
		s_len--;
	}
	if (check == -1)
		str[0] = '-';
	return (str);
}
/*
** Allocates (with malloc()) and returns a string
** representing the integer received as an argument.
** Negative numbers must be handled.
** If successful, returns a string representing an integer.
** Returns NULL on failure, or allocation failure.
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:51:42 by sna               #+#    #+#             */
/*   Updated: 2022/03/15 21:54:44 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

void	sort_envs(char **temp, char **envs, int size)
{
	int		i;
	int		step;
	char	*temp_str;

	step = 0;
	i = -1;
	while (envs[++i])
		temp[i] = ft_strdup(envs[i]);
	temp[i] = NULL;
	while (step < size - 1)
	{
		i = 0;
		while (i < size - 1 - step)
		{
			if (ft_strcmp2(temp[i], temp[i + 1]) > 0)
			{
				temp_str = temp[i];
				temp[i] = temp[i + 1];
				temp[i + 1] = temp_str;
			}
			i++;
		}
		step++;
	}
}

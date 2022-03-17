/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:35:30 by sna               #+#    #+#             */
/*   Updated: 2022/03/17 14:35:31 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

char	**copy_envs(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}

char	*find_value(char *input, char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (!ft_strncmp(envs[i], input, ft_strlen(input)))
			return (envs[i] + ft_strlen(input) + 1);
	}
	return ("");
}

int	arr_2dchar_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_env(char *str, char *envs)
{
	int		i;

	i = 0;
	while (str[i] && envs[i] && (str[i] == envs[i]) && (str[i] != '=')
		&& (envs[i] != '='))
		i++;
	if (i == 0)
		return (0);
	if (((envs[i] == '=') && (str[i] == '='))
		|| ((envs[i] == '=') || str[i] == 0))
		return (1);
	return (0);
}

void	copy_env_to_new(char **new, char ***c_envs, int *i)
{
	while ((*c_envs)[++(*i)])
	{
		new[*i] = ft_strdup((*c_envs)[*i]);
		free((*c_envs)[*i]);
	}
}

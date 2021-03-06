/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:36:18 by sna               #+#    #+#             */
/*   Updated: 2022/03/17 15:40:58 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_prec.h"

void	echo_exit_status(void)
{
	ft_putstr_fd(ft_itoa(g_exit_status), 1);
}

void	echo_envs(char **cmd_line, char **envs, int i)
{
	char	*value;

	if (cmd_line[1][0] == '$' && cmd_line[1][1] == '?')
		echo_exit_status();
	value = find_value(&(cmd_line[i][1]), envs);
	ft_putstr_fd(value, 0);
}

int	is_option_n(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	if (ft_strncmp(str, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	built_echo(char **cmd_line)
{
	int	i;
	int	res;

	i = 1;
	res = 0;
	while (is_option_n(cmd_line[i]))
	{
		res = -1;
		i++;
	}
	while (cmd_line[i])
	{
		ft_putstr_fd(cmd_line[i], 1);
		if (cmd_line[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (res != -1)
		ft_putchar_fd('\n', 1);
}

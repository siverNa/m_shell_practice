/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:36:10 by sna               #+#    #+#             */
/*   Updated: 2022/03/17 14:36:11 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_prec.h"

int	isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	start_exit(void)
{
	exit(g_exit_status);
}

void	built_exit(t_node *cmd, char **cmd_line)
{
	int	ac;

	ac = 0;
	if (cmd->pre_status == 1)
		return ;
	while (cmd_line[ac] != NULL)
		ac++;
	if (ac == 1)
		start_exit();
	else if (ac == 2 && isdigit_str(cmd_line[1]))
		g_exit_status = ft_atoi(cmd_line[1]);
	else if (ac > 2 && isdigit_str(cmd_line[1]))
	{
		ft_putstr_fd("exit\n", STDERR);
		print_error_msg("exit", "too many arguments");
		g_exit_status = 1;
		return ;
	}
	else
	{
		print_error_msg_2("exit", cmd_line[1], "numeric argument required");
		g_exit_status = 255;
		exit (g_exit_status & 255);
	}
	start_exit();
}

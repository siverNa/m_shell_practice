/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:32:07 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/20 22:42:52 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

int	print_exe_error_msg(t_node *cmd)
{
	ft_putstr_fd("practice : command not found: ", 2);
	ft_putstr_fd(cmd->cmd_line[0], 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	print_error_msg(char *input, char *err_msg)
{
	ft_putstr_fd("practice", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	return (-1);
}

int	print_error_msg_2(char *first, char *sec, char *err_msg)
{
	ft_putstr_fd("practice", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(first, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(sec, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	return (-1);
}

int	print_identify_error_msg(char *first, char *sec)
{
	ft_putstr_fd("practice", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(first, STDERR);
	ft_putstr_fd(": `", STDERR);
	ft_putstr_fd(sec, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	return (0);
}

int	print_errno(char *cmd, int res)
{
	if (errno)
	{
		ft_putstr_fd("minishell", STDERR);
		ft_putstr_fd(": ", STDERR);
		if (cmd)
		{
			ft_putstr_fd(cmd, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd(strerror(errno), STDERR);
	}
	return (res);
}

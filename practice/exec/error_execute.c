/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:32:07 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/21 17:16:23 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

int	print_exe_error_msg(t_node *cmd)
{
	ft_putstr_fd("minishell : command not found: ", STDERR);
	ft_putstr_fd(cmd->cmd_line[0], STDERR);
	ft_putstr_fd("\n", STDERR);
	return (-1);
}

int	print_error_msg(char *input, char *err_msg)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(input, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (-1);
}

int	print_error_msg_2(char *first, char *sec, char *err_msg)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(first, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(sec, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (-1);
}

int	print_identify_error_msg(char *first, char *sec)
{
	ft_putstr_fd("minishell", STDERR);
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

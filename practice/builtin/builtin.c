/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:35:43 by sna               #+#    #+#             */
/*   Updated: 2022/03/17 15:40:35 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

int	check_builtin(char **cmd_line)
{
	char	*builtin;

	builtin = cmd_line[0];
	if (!ft_strncmp(builtin, "echo", 4) || !ft_strncmp(builtin, "cd", 2)
		|| !ft_strncmp(builtin, "pwd", 3) || !ft_strncmp(builtin, "export", 6)
		|| !ft_strncmp(builtin, "unset", 5) || !ft_strncmp(builtin, "env", 3)
		|| !ft_strncmp(builtin, "exit", 4))
		return (TRUE);
	return (FALSE);
}

int	start_builtin(t_node *cmd, char **cmd_line, t_data *input)
{
	char	*builtin;

	builtin = cmd->cmd_line[0];
	if (!ft_strncmp(builtin, "cd", 2))
		built_cd(cmd_line, input->env);
	else if (!ft_strncmp(builtin, "echo", 4))
		built_echo(cmd_line);
	else if (!ft_strncmp(builtin, "pwd", 3))
		built_pwd();
	else if (!ft_strncmp(builtin, "env", 3))
		built_env(input->env);
	else if (!ft_strncmp(builtin, "export", 6))
		built_export(cmd, cmd_line, input);
	else if (!ft_strncmp(builtin, "unset", 5))
		built_unset(cmd, cmd_line, input);
	else if (!ft_strncmp(builtin, "exit", 4))
		built_exit(cmd, cmd_line);
	else
		return (0);
	return (1);
}

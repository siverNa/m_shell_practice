/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 23:47:41 by sna               #+#    #+#             */
/*   Updated: 2022/03/17 15:38:28 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_prec.h"

int	built_cd(char **cmd_line, char **c_envs)
{
	int		i;

	i = -1;
	if (arr_2dchar_len(cmd_line) == 1 || cmd_line[1][0] == '~')
	{
		while (c_envs[++i])
		{
			if (check_env("HOME=", c_envs[i]))
				return (start_cd(c_envs[i] + 5, c_envs));
		}
		return (start_cd(c_envs[i] + 5, c_envs));
	}
	else
		return (start_cd(cmd_line[1], c_envs));
}

int	start_cd(char *input, char **c_envs)
{
	int		res;
	char	*path;

	res = chdir(input);
	if (res == 0)
	{
		path = malloc(sizeof(char) * 1024);
		if (!path)
			return (ERROR);
		path = getcwd(path, 1024);
		if (!path)
			return (ERROR);
		set_cd_pwd(path, c_envs);
		free(path);
	}
	else
	{
		print_error_msg_2("cd", input, "No such file or directory");
		g_exit_status = 1;
		return (ERROR);
	}
	g_exit_status = 0;
	return (SUCCESS);
}

void	set_cd_pwd(char *path, char **c_envs)
{
	char	*ch_path;
	char	*old_pwd;

	ch_path = ft_strjoin("PWD=", path);
	old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", c_envs));
	start_export(ch_path, &c_envs);
	start_export(old_pwd, &c_envs);
	free(ch_path);
	free(old_pwd);
}

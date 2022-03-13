/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 23:47:41 by sna               #+#    #+#             */
/*   Updated: 2022/03/14 01:24:52 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

/*int	exec_cd_home(char *path, char **cmd_line, char **c_envs)
{
	printf("i m inside function!\n");
	if (cmd_line[1][1] == '~')
	{
		print_error_msg_2("cd", cmd_line[1], "No such file or directory");
		g_exit_status = 1;
	}
	path = find_value("HOME", c_envs);
	if (chdir(path) == -1)
		print_error_msg("cd", "fail move HOME");
	return (1);
}

int	exec_cd_envs(char *path, char **cmd_line, char **c_envs)
{
	path = find_value(&(cmd_line[1][1]), c_envs);
	if (chdir(path) == -1)
		chdir(find_value("HOME", c_envs));
	return (1);
}

void	set_pwd(char **c_envs)
{
	char	*cur_pwd;
	char	*old_pwd;
	char	*temp;

	temp = malloc(sizeof(char) * 1024);
	if (!temp)
		return ;
	cur_pwd = ft_strjoin("PWD=", getcwd(temp, 1024));
	free (temp);
	old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", c_envs));
	check_export(cur_pwd, &c_envs);
	check_export(old_pwd, &c_envs);
	free(cur_pwd);
	free(old_pwd);
}

void	built_cd(char **cmd_line, char **c_envs)
{
	char	*path;
	int		res;

	path = 0;
	res = 0;
	printf("cmdline[1] : %s\n", cmd_line[1]);
	if (cmd_line[1] != NULL && cmd_line[1][0] != '~' && cmd_line[1][0] != '$')
	{
		path = cmd_line[1];
		if (chdir(path) == -1)
			res = print_error_msg_2("cd", path, strerror(errno));
		set_pwd(c_envs);
	}
	else if (cmd_line[1] == NULL || cmd_line[1][0] == '~')
	{
		printf("i m inside if!\n");
		exec_cd_home(path, cmd_line, c_envs);
	}
	else if (cmd_line[1][0] == '$')
		exec_cd_envs(path, cmd_line, c_envs);
	if (res == -1)
		g_exit_status = 1;
	else
		g_exit_status = 0;
}*/

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
	char	*ch_path;
	char	*old_pwd;

	res = chdir(input);
	if (res == 0)
	{
		path = malloc(sizeof(char) * 1024);
		if (!path)
			return (ERROR);
		path = getcwd(path, 1024);
		if (!path)
			return (ERROR);
		set_cd_pwd(ch_path, old_pwd, path, c_envs);
		free(path);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

void	set_cd_pwd(char *ch_path, char *old_pwd, char *path, char **c_envs)
{
	ch_path = ft_strjoin("PWD=", path);
	old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", c_envs));
	start_export(ch_path, &c_envs);
	start_export(old_pwd, &c_envs);
	free(ch_path);
	free(old_pwd);
}

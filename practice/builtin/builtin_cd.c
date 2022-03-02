#include "../minishell_prec.h"

int	exec_cd_home(char *path, char **cmd_line, char **c_envs)
{
	if (cmd_line[1][1] == '~')
		print_error_msg_2("cd", cmd_line[1], "No such file or directory");
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
	if (cmd_line[1] != NULL && cmd_line[1][0] != '~' && cmd_line[1][0] != '$')
	{
		path = cmd_line[1];
		if (chdir(path) == -1)
			res = print_error_msg_2("cd", path, strerror(errno));
		set_pwd(c_envs);
	}
	else if (cmd_line[1] == NULL || cmd_line[1][0] == '~')
		exec_cd_home(path, cmd_line, c_envs);
	else if (cmd_line[1][0] == '$')
		exec_cd_envs(path, cmd_line, c_envs);
	if (res == -1)
		ft_putendl_fd("error", 2);
}

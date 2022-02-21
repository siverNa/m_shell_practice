#include "minishell_prec.h"

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

int	start_builtin(t_node *cmd, char **cmd_line)
{
	char	*builtin;

	builtin = cmd->cmd_line[0];
	if (!ft_strncmp(builtin, "cd", 2))
		built_cd(cmd_line, cmd->c_envs);
	else if (!ft_strncmp(builtin, "echo", 4))
		ft_putendl_fd("you type echo!", 1);
	else if (!ft_strncmp(builtin, "pwd", 3))
		ft_putendl_fd("you type pwd!", 1);
	else if (!ft_strncmp(builtin, "env", 3))
		ft_putendl_fd("you type env!", 1);
	else if (!ft_strncmp(builtin, "export", 6))
		ft_putendl_fd("you type export!", 1);
	else if (!ft_strncmp(builtin, "unset", 5))
		ft_putendl_fd("you type unset!", 1);
	else if (!ft_strncmp(builtin, "exit", 4))
		ft_putendl_fd("you type exit!", 1);
	else
		return (0);
	return (1);
}

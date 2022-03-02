#include "minishell_prec.h"

void	free_struct(t_node *cmd, char *str)
{
	free(str);
	free(cmd->file_path);
	free_cmdline(cmd->cmd_line);
	str = NULL;
	cmd->file_path = NULL;
	cmd->cmd_line = NULL;
}

void	child_process(t_node *cmd, char *str)
{
	int	res;

	res = 0;
	if ((check_builtin(cmd->cmd_line) == TRUE))
		start_builtin(cmd, cmd->cmd_line);
	else if (execve(cmd->file_path, cmd->cmd_line, cmd->c_envs) == -1)
	{
		ft_putstr_fd("practice : command not found: ", 2);
		ft_putstr_fd(cmd->cmd_line[0], 2);
		ft_putstr_fd("\n", 2);
		free_struct(cmd, str);
		exit(1);
	}
	else
		return ;
}

int	start_pipe(t_node *cmd, char *str)
{
	pid_t	pid;
	int		status;
	int		res;

	res = 0;
	pid = fork();
	if (pid == 0)
		child_process(cmd, str);
	waitpid(pid, &status, 0);
}

void	process(t_node *cmd, char *str)
{
	if (cmd->cmd_line[0])
	{
		if ((check_builtin(cmd->cmd_line) == TRUE))
			start_builtin(cmd, cmd->cmd_line);
		else
			start_pipe(cmd, str);
	}
}

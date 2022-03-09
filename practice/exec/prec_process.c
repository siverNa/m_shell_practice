#include "../minishell_prec.h"

void	free_struct(t_node *cmd)
{
	free(cmd->file_path);
	free_cmdline(cmd->cmd_line);
	cmd->file_path = NULL;
	cmd->cmd_line = NULL;
}

void	child_process(t_node *cmd, t_data *input, char *str, t_node *n_cmd)
{
	int		res;
	char	*path;

	res = 0;
	path = build_path(cmd, input, cmd->cmd_line[0]);
	/*if (cmd->status == 1)
	{
		if (dup2(n_cmd->fd[1], STDOUT) == -1)
			exit(-1);
		close(n_cmd->fd[1]);
	}
	if (cmd->fd[0] != 0)
	{
		if (dup2(cmd->fd[0], STDIN) == -1)
			exit(-1);
		close(cmd->fd[0]);
	}*/
	if ((check_builtin(cmd->cmd_line) == TRUE))
		start_builtin(cmd, cmd->cmd_line, input);
	else
		res = execve(path, cmd->cmd_line, input->env);
	if (res == -1)
		print_exe_error_msg(cmd, str);
	exit(res);
}

int	start_pipe(t_node *cmd, t_data *input, char *str)
{
	pid_t	pid;
	int		status;
	int		res;
	t_node	*n_cmd;

	res = 0;
	if (cmd->status == 1)
	{
		n_cmd = cmd->next;
		printf("%s\n", n_cmd->cmd_line[0]);
		pipe(n_cmd->fd);
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd, input, str, n_cmd);
	waitpid(pid, &status, 0);
	if (cmd->status == 1)
		close(n_cmd->fd[1]);
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	return (res);
}

void	process(t_node *cmd, t_data *input, char *str)
{
	while (cmd != NULL)
	{
		if (cmd->cmd_line[0])
		{	
			if ((check_builtin(cmd->cmd_line) == TRUE) && cmd->status == 0)
				start_builtin(cmd, cmd->cmd_line, input);
			else
			{
				start_pipe(cmd, input, str);
				if (cmd->next != NULL)
					cmd = cmd->next;
			}
		}
		cmd = cmd->next;
	}
}

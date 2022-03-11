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
	if (cmd->status == 1)
	{
		dup2(n_cmd->fd[1], STDOUT);
		close(n_cmd->fd[1]);
	}
	if (cmd->fd[0] != 0)
	{
		dup2(cmd->fd[0], STDIN);
		close(cmd->fd[0]);
	}
	if (cmd->redir == 1)
		redirect(input, cmd);
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
	n_cmd = cmd;
	if (cmd->status == 1)
	{
		n_cmd = cmd->next;
		n_cmd-> pre_status = 1;
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

void	builtin_redir_nopipe(t_node *cmd, t_data *input)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		redirect(input, cmd);
		start_builtin(cmd, cmd->cmd_line, input);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return ;
}

void	process(t_node *cmd, t_data *input, char *str)
{
	while (cmd != NULL)
	{
		if (cmd->cmd_line[0])
		{
			//print command line
			cmd->here_doc = 0;
			printf("CMD_LINE: ");
			int i = 0;
			while (cmd->cmd_line[i])
				printf("[%s]", cmd->cmd_line[i++]);
			printf("\n");

			if ((check_builtin(cmd->cmd_line) == TRUE) && cmd->status == 0)
			{
				if (cmd->redir == 0)
					start_builtin(cmd, cmd->cmd_line, input);
				else
					builtin_redir_nopipe(cmd, input);
			}
			else
				start_pipe(cmd, input, str);
		}
		if (cmd->here_doc != 0)
			unlink(".temp");
		cmd = cmd->next;
	}
}

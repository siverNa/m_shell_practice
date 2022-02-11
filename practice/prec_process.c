#include "minishell_prec.h"

void	free_struct(t_node *cmd, char *str)
{
	free(str);
	free_cmdline(cmd->cmd_line);
	str = NULL;
}

void child_process(t_node *cmd, char *str, char **env)
{
	if (!strcmp(cmd->cmd_line[0], "ls"))
	{
		if (execve("/usr/bin/ls", cmd->cmd_line, env) == -1)
		{
			ft_putstr_fd("practice : command not found: ", 2);
			ft_putstr_fd(cmd->cmd_line[0], 2);
			ft_putstr_fd("\n", 2);
			free_struct(cmd, str);
			exit(1);
		}
	}
}

void process(t_node *cmd, char *str, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(1);
	}
	else if (pid > 0)
	{
		//waitpid(pid, &cmd->status, WNOHANG);
		wait(NULL);
		return ;
	}
	else if (pid == 0)
	{
		child_process(cmd, str, env);
	}
	return ;
}
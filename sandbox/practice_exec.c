#include "minishell_prec.h"

void    convert_cmd(t_node *cmd, char **)

void    exec_cmd(t_node *cmd)
{
    char a[][2] = {"ls", "-a", "-l"};

	write(1, "enter\n", 6);
	int	pid;
	pid = fork();
	if (pid == -1)
	{
		write(1, "ERROR\n", 6);
		return ;
	}
	if (pid == 0)
	{
/*
*/
		if (execlp("ls", "ls", "-la", NULL) < 0)
            write(1, "FAIL\n", 5);
        //왜 이렇게 하나하나 입력해주면 되는데, cmd->cmd->line으로 인자를 주면 에러?
        return ;
	}
	else
	{
		wait(NULL);
		write(1, "parent\n", 7);
		write(1, "SUCCESS\n", 8);

        return ;
	}

	return ;

}
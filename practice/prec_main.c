#include "minishell_prec.h"

void free_cmdline(char **cmdline)
{
	int i;
	
	i = 0;
	while (cmdline[i])
	{	
		free(cmdline[i]);
		cmdline[i] = NULL;
		i++;
	}
	free(cmdline);
	cmdline = NULL;
}

void sig_handler(int signum)
{
	if (signum != SIGINT)
		return;
	printf("\b\bctrl + c\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	t_node	cmd;
	char	*str;
	int		i;

	signal(SIGINT, sig_handler);
	while(1)
	{
		str = readline("practice : ");
		if (str == NULL)
		{
			free(str);
			continue ;
		}
		if (*str == '0')
		{
			free(str);
			str = NULL;
			break ;
		}
		cmd.cmd_line = ft_split(str, ' ');
		i = 0;
		while (cmd.cmd_line[i])
			printf("splited[%d] : %s\n", i++, cmd.cmd_line[i]);
		add_history(str);
		free(str);
		free_cmdline(cmd.cmd_line);
		str = NULL;
	}
	return (0);
}

/*
 compile command
 gcc prec_main.c deque_func.c -lreadline 
-L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib 
-I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include -L../libft -lft 
-g3 -fsanitize=address
*/
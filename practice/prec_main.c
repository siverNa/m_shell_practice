#include "minishell_prec.h"

void	free_cmdline(char **cmdline)
{
	int	i;

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

void	sig_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("ctrl + c\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	setting_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_node			cmd;
	char			*str;
	int				i;
	struct termios	org_term;
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &org_term);
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	setting_signal();
	while (1)
	{
		str = readline("practice : ");
		if (!str)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit(-1);
		}
		else if (*str == '\0')
			free(str);
		else
		{
			cmd.cmd_line = ft_split(str, ' ');
			i = 0;
			while (cmd.cmd_line[i])
				printf("splited[%d] : %s\n", i++, cmd.cmd_line[i]);
			//cmd.cmd_line = cmd_init(str);
			cmd.file_path = build_path(&cmd, cmd.cmd_line[0], env);
			process(&cmd, str, env);
			add_history(str);
			//free(str);
			//free_cmdline(cmd.cmd_line);
			//str = NULL;
			free_struct(&cmd, str);
		}
	}
	return (0);
}

/*
 compile command
 gcc prec_main.c prec_process.c cmd_init.c cmd_case.c cmd_build_path.c -lreadline 
-L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib 
-I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include -L../libft -lft 
-g3 -fsanitize=address
*/
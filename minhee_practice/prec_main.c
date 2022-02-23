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
	t_data			input;
	t_node			*cmds;
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
		input.str = readline("practice : ");
		if (!input.str)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit(-1);
		}
		else if (*(input.str) == '\0')
			free((input.str));
		else
		{
			input.buf = ft_split(input.str, ' ');
			cmds = parse(input.buf);
/*
			cur = *cmds;
			while (cur)
			{
				//exec
				//testing: prints cur.cmdline;
				cur = cur.next;
			}
*/			
			add_history(input.str);
			free(input.str);
			//free_cmdline(cmd.cmd_line);
			input.str = NULL;
		}
	}
	return (0);
}

/*
 compile command
 gcc prec_main.c prec_process.c -lreadline 
-L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib 
-I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include -L../libft -lft 
-g3 -fsanitize=address
*/
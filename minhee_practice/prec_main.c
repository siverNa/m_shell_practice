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
	int				i, k;
	struct termios	org_term;
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &org_term);
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	setting_signal();
	input.env = NULL;
	input.env = copy_envs(env);
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
			input.tokens = tokenize(input.str, input.env);
			write(1, "------------------------------\n", 31);
			printf("printing tokens\n");
			i = 0;
			while (input.tokens[i])
			{
				printf("token[%d]: [%s]\n", i, input.tokens[i]);
				i++;
			}
			write(1, "------------------------------\n", 31);
			cmds = parse(input.tokens);
			if (cmds == NULL)
				printf("cmds is NULL\n");
			k = 0;
			while (cmds != NULL)
			{
				printf("command[%d]: ", k);
				i = 0;
				while (cmds->cmd_line[i] != NULL)
				{
					printf("(%s) ", cmds->cmd_line[i]);
					i++;
				}
				printf("\n");
				cmds = cmds->next;
				k++;
			}
			printf("end of cmds\n");
			write(1, "------------------------------\n", 31);
			add_history(input.str);
			free(input.str);
			i = 0;
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

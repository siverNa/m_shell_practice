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
	input.env = NULL;
	input.env = copy_envs(env);
	while (1)
	{
		input.str = readline("\033[34;1mpractice : \033[0m");
		if (!(input.str))
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit(-1);
		}
		else if (*(input.str) == '\0')
			free(input.str);
		else
		{
			input.tokens = tokenize(input.str, input.env);
			i = 0;
			while (input.tokens[i])
			{
				printf("tokenized:[%d] : %s\n", i, input.tokens[i]);
				i++;
			}
			//cmd.cmd_line = cmd_init(str);
			cmds = parse(input.tokens);
			while (cmds != NULL)
			{
				cmds->file_path = build_path(cmds, cmds->cmd_line[0]);
				process(cmds, input.str);
				add_history(input.str);
				cmds = cmds->next;
			}
			//free(str);
			//free_cmdline(cmd.cmd_line);
			//str = NULL;
			//free_struct(&cmd, str);
		}
	}
	//free_cmdline(cmd.c_envs);
	return (0);
}

/*
 compile command
 gcc prec_main.c prec_process.c cmd_init.c cmd_case.c cmd_build_path.c builtin.c 
builtin_cd.c builtin_pwd.c builtin_env.c builtin_export.c builtin_echo.c builtin_unset.c builtin_exit.c env_util.c error_execute.c -lreadline 
-L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib 
-I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include -L../libft -lft 
-g3 -fsanitize=address
*/

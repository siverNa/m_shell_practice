#include "minishell_prec.h"

int g_exit_status = 0;

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
	t_node			*list;
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
			while (input.tokens[i].type != -1)
			{
				printf("tokenized:[%d] : %s\n", i, input.tokens[i].value);
				i++;
			}
			if (check_syntax(&input) == -1)
				continue ;
			list = parse(input.tokens);
			cmds = list;
			process(cmds, &input, input.str);
			add_history(input.str);
			free(input.str);
			free_tokens(input.tokens);
			free_cmds_list(list);
			list = NULL;
		}
	}
	//free_cmdline(cmd.c_envs);
	return (g_exit_status & 255);
}

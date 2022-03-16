#include "minishell_prec.h"

int	g_exit_status = 0;

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

void	sig_handler2(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			ft_putstr_fd(" \n", 1);
			rl_replace_line("", 1);
			rl_redisplay();
			ft_putstr_fd("  \b\b", 1);
		}
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	sig_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			ft_putstr_fd(" \n", 1);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", 1);
	}
}

void	setting_signal(void)
{
	struct termios	org_term;
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &org_term);
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler2);
}

void	shell_ready(t_data *input, t_node *cmds, t_node *list)
{
	input->tokens = tokenize(input->str, input->env);
	if (check_syntax(input) == -1)
		return ;
	list = parse(input->tokens);
	cmds = list;
	process(cmds, input, input->str);
	add_history(input->str);
	free(input->str);
	free_tokens(input->tokens);
	free_cmds_list(list);
	list = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data			input;
	t_node			*cmds;
	t_node			*list;

	setting_signal();
	(void)ac;
	(void)av;
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
			shell_ready(&input, list, cmds);
	}
	return (g_exit_status & 255);
}

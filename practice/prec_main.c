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

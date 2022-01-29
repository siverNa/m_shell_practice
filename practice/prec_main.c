#include "minishell_prec.h"

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
	t_deq	cmd;
	char	*str;
	int		i;

	signal(SIGINT, sig_handler);
	init_cmd(&cmd);
	while(1)
	{
		str = readline("practice : ");
		//node.cmd_line = ft_split(str, ' ');
		if (*str == '0')
		{
			free(str);
			str = NULL;
			break ;
		}
		insert_str(&cmd, str);
		i = 0;
		while (cmd.tail->cmd_line[i])
			printf("splited[%d] : %s\n", i++, cmd.tail->cmd_line[i]);
		add_history(str);
		free(str);
		str = NULL;
	}
	i = 0;
	t_node	*temp;
	temp = cmd.head;
	while (i < cmd.size)
	{
		int j;
		j = 0;
		while (temp->cmd_line[j])
			printf("stored str : %s\n", temp->cmd_line[j++]);
		temp = temp->next;
		i++;
	}
	free_deq(&cmd);
	return (0);
}

/*
 comfile command
 gcc prec_main.c deque_func.c -lreadline 
-L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib 
-I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include -L../libft -lft 
-g3 -fsanitize=address
*/
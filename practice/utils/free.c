#include "../minishell_prec.h"

void	free_node_cmdline(t_node *node)
{
	printf(">free cmd<\n");
	int	i;

	i = 0;
	while (node->cmd_line[i] != NULL)
	{
		printf("free cmd[%d]: [%s]\n", i, node->cmd_line[i]);
		free(node->cmd_line[i]);
		i++;
	}
	printf("cmd_line tokens are freed!\n");
	free(node->cmd_line);
	printf("exiting free_node_cmdline\n");
	return ;
}

void	free_cmds_list(t_node *list)
{
	printf("entered free list\n");
	t_node	*cur;
	t_node	*temp;

	cur = list;
	while (cur != NULL)
	{
		free_node_cmdline(cur);
		cur = cur->next;
	}
	cur = list;
	while (cur != NULL)
	{
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	printf("exiting free list\n");
	return ;
}

void	free_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].value != NULL)
	{
		free(token[i].value);
		i++;
	}
	free(token);
	return ;
}

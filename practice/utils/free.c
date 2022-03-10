#include "../minishell_prec.h"

void	free_node_cmdline(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd_line[i] != NULL)
	{
		free(node->cmd_line[i]);
		i++;
	}
	free(node->cmd_line);
	return ;
}

void	free_cmds_list(t_node *list)
{
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

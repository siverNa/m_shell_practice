#include "minishell_prec.h"

void free_cmdline(char **cmdline)
{
	int i;
	
	i = 0;
	while (cmdline[i])
		free(cmdline[i++]);
	free(cmdline);
	cmdline = NULL;
}

void free_deq(t_deq *cmd)
{
	t_node	*temp;

	while (cmd->head)
	{
		temp = cmd->head;
		cmd->head = cmd->head->next;
		free_cmdline(temp->cmd_line);
		free(temp);
	}
}

void init_cmd(t_deq *deq)
{
	deq->size = 0;
	deq->head = NULL;
	deq->tail = NULL;
}

int	dq_is_empty(t_deq *d)
{
	if (d->head == NULL)
		return (TRUE);
	else
		return (FALSE);
}

void lst_addend(t_deq *deq, char *str)
{
	t_node		*newnode;

	newnode = (t_node *)malloc(sizeof(t_node));
	if (!newnode)
		return ;
	newnode->cmd_line = ft_split(str, ' ');
	newnode->prev = deq->tail;
	if (dq_is_empty(deq))
		deq->head = newnode;
	else
		deq->tail->next = newnode;
	newnode->next = NULL;
	deq->tail = newnode;
}

void insert_str(t_deq *deq, char *str)
{
	lst_addend(deq, str);
	deq->size++;
}
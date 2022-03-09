#include "../minishell_prec.h"

void    add_list_back(t_node **list, t_node *new_node)
{
    t_node   *cur;

    if (list == 0 || new_node == 0)
		return ;
	if (*list == 0)
		*list = new_node;
	else
	{
		cur = *list;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new_node;
	}
    return ;
}

t_node   *parse(t_token *tokens)
{
    t_node   *list;
    t_node   *new_node;
    int i, j, k;

    list = NULL;

    i = 0;
    while (tokens[i].value != NULL)
    {
        new_node = (t_node *)malloc(sizeof(t_node));
        if (new_node == NULL)
            exit(1);
		new_node->start = i;
		
		//make cmd_line
        j = i;
        while (tokens[j].type == 0)
            j++;
        new_node->cmd_line = (char **)malloc(sizeof(char *) * (j - i + 1));
        if (new_node->cmd_line == NULL)
            exit(1);
        k = 0;
        while (i < j)
		{
            new_node->cmd_line[k] = ft_strdup(tokens[i].value);
			k++;
			i++;
		}
        new_node->cmd_line[k] = NULL;
        new_node->next = NULL;
        new_node->status = 0;
		//parse command
		if (tokens[i].type == 2)
			new_node->redir = 1;
		while (tokens[i].type != -1 && tokens[i].type != 1)
			i++;
        if (tokens[i].type == 1)
		{
            new_node->status = 1;
			i++;
		}
		new_node->last = i - 1;
        add_list_back(&list, new_node);
    }
	free_tokens(tokens);
    return (list);
}

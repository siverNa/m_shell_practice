#include "../minishell_prec.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    if (s1 == NULL)
    {
        if (s2 == NULL)
            return (1);
        else
            return (0);
    }

    i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
    if (s1[i] == s2[i])
        return (1);
    else
        return (0);
}

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

t_node   *parse(char **buf)
{
    t_node   *list;
    t_node   *new_node;
    int i, j, k;

    list = NULL;

    i = 0;
    while (buf[i] != NULL)
    {
        new_node = (t_node *)malloc(sizeof(t_node));
        if (new_node == NULL)
            exit(1);
        j = i;
        while (buf[j] != NULL && ft_strcmp(buf[j], "|") == 0)
            j++;
        new_node->cmd_line = (char **)malloc(sizeof(char *) * (j - i + 1));
        if (new_node->cmd_line == NULL)
            exit(1);
        k = 0;
        while (i < j)
		{
            new_node->cmd_line[k] = ft_strdup(buf[i]);
			k++;
			i++;
		}
        new_node->cmd_line[k] = NULL;
        new_node->next = NULL;
        new_node->status = 0;
        if (ft_strcmp(buf[i], "|"))
            new_node->status = 1;
        if (buf[i] != NULL)
            i++;
        add_list_back(&list, new_node);
    }
	free_tokens(buf);
    return (list);
}

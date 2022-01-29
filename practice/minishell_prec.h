#ifndef MINISHELL_PREC_H
# define MINISHELL_PREC_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# define TRUE		1
# define FALSE		0

typedef struct		s_node
{
	char			**cmd_line;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct		s_deq
{
	int				size;
	t_node			*head;
	t_node			*tail;
}					t_deq;

/*
** deque_func.c
*/
void	free_cmdline(char **cmdline);
void	free_deq(t_deq *cmd);
void	init_cmd(t_deq *deq);
int		dq_is_empty(t_deq *d);
void	lst_addend(t_deq *deq, char *str);
void	insert_str(t_deq *deq, char *str);

#endif
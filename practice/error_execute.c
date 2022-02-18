#include "minishell_prec.h"

int		print_error_msg(char *input, char *err_msg)
{
	ft_putstr_fd("practice", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	return (-1);
}

int		print_error_msg_2(char *first, char *sec, char *err_msg)
{
	ft_putstr_fd("practice", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(first, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(sec, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	return (-1);
}
#include "../minishell_prec.h"

int	print_exe_error_msg(t_node *cmd, char *str)
{
	ft_putstr_fd("practice : command not found: ", 2);
	ft_putstr_fd(cmd->cmd_line[0], 2);
	ft_putstr_fd("\n", 2);
	free(str);
	free_struct(cmd);
	return (-1);
}

int	print_error_msg(char *input, char *err_msg)
{
	ft_putstr_fd("practice", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	return (-1);
}

int	print_error_msg_2(char *first, char *sec, char *err_msg)
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

void	print_identify_error_msg(char *first, char *sec)
{
	ft_putstr_fd("practice", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(first, STDERR);
	ft_putstr_fd(": `", STDERR);
	ft_putstr_fd(sec, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
}

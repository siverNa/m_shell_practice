#include "../minishell_prec.h"

void	built_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 1024);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_exit_status = 0;
}

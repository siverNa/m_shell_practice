#include "minishell_prec.h"

void	built_pwd(void)
{
	char	*pwd;

	errno = 0;
	pwd = getcwd(0, 1024);
	//if (!pwd);
	//{
	//	strerror(errno);
	//	exit(1);
	//}
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
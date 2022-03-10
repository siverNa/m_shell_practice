#include "../minishell_prec.h"

void	built_env(char **c_envs)
{
	int		i;

	i = 0;
	while (c_envs[i])
	{
		ft_putendl_fd(c_envs[i], 1);
		i++;
	}
	g_exit_status = 0;
}

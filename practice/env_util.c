#include "minishell_prec.h"

char	*find_value(char *input, char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (!ft_strncmp(envs[i], input, ft_strlen(input)))
			return (envs[i] + ft_strlen(input) + 1);
	}
	return ("");
}
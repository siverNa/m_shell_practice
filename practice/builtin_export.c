#include "minishell_prec.h"

void	add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

int	check_export(char *str, char ***envs)
{
	int		i;
	char	**new;

	if (str[0] == '=' || str[0] == '\0' || ft_strlen(str) == 1)
		return (-1);
	i = -1;
	while ((*envs)[++i] != NULL)
	{	
		if (!ft_strncmp((*envs)[i], str, ft_strlen(str)))
		{
			(*envs)[i] = ft_strdup(str);
			return (1);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (-1);
	i = -1;
	while ((*envs)[++i])
		new[i] = ft_strdup((*envs)[i]);
	add_export(str, new, i);
	*envs = new;
	return (1);
}

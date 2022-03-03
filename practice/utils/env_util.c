#include "../minishell_prec.h"

char	**copy_envs(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}

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

int	arr_2dchar_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strtok(char *str, char c)
{
	static char	*stock = NULL;
	char		*p;
	int			status;

	status = 0;
	p = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (status == 0 && *stock != c)
		{
			status = 1;
			p = stock;
		}
		else if (status == 1 && *stock == c)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	if (*stock == '\0')
		free(stock);
	return (p);
}

#include "../minishell_prec.h"

void	get_env_token(char **token, char **env, char *var_name)
{
	char	*value;
	int		i;

	value = find_value(var_name, env);
	i = 0;
	while (value[i])
		concat_char(token, value[i++]);
	return ;
}

int	get_exit_status(char **token, int j)
{
	char	*exit_status;
	int		i;

	exit_status = ft_itoa(g_exit_status);
	i = 0;
	while (exit_status[i])
	{
		concat_char(token, exit_status[i]);
		i++;
	}
	free(exit_status);
	return (j + 1);
}

int	check_quote(char *str, int i, char quote)
{
	int	ret;

	if (str == NULL)
		return (0);
	ret = i + 1;
	while (str[ret])
	{
		if (str[ret] == quote)
			return (ret);
		ret++;
	}
	if (str[ret] == 0)
		return (i);
	else
		return (ret);
}

void	concat_char(char **str, char c)
{
	char	*temp;
	int		i;
	int		size;

	if (*str == NULL)
		size = 0;
	else
		size = ft_strlen(*str);
	temp = (char *)malloc(sizeof(char) * (size + 2));
	if (temp == NULL)
	{
		free(*str);
		exit(1);
	}
	i = 0;
	while (i < size)
	{
		temp[i] = (*str)[i];
		i++;
	}
	temp[i] = c;
	temp[i + 1] = 0;
	free(*str);
	*str = temp;
	return ;
}

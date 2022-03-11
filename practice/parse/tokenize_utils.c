#include "../minishell_prec.h"

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

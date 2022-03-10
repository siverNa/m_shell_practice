#include "../minishell_prec.h"

char	**parsing_str(char *str, char **result, t_pars *pars)
{
	pars->i = 0;
	pars->j = 0;
	while (str[pars->i] != '\0' && pars->j < pars->len)
	{
		pars->count = 0;
		if (str[pars->i] != ' ')
		{
			if (str[pars->i] == 34)
				case_double_q(str, result, pars);
			else if (str[pars->i] == 39)
				case_single_q(str, result, pars);
			else
				case_space(str, result, pars);
		}
		result[pars->j][pars->count] = '\0';
		pars->i++;
		pars->j++; 
	}
	result[pars->j] = 0;
	return (result);
}

void	count_word(const char *str, int *i, int *count)
{
	if (str[*i] == 34)
	{
		(*i)++;
		while (str[*i] != 34 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] != 39 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else
	{
		while (str[*i] != ' ' && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
}

int	count_str(const char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			count_word(str, &i, &count);
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (count);
}

char	**cmd_init(const char *str)
{
	t_pars	pars;
	char	**result;

	if (str == NULL)
		return (NULL);
	pars.len = count_str(str);
	result = (char **)malloc(sizeof(char *) * pars.len + 1);
	if (!result)
		return (NULL);
	return (parsing_str((char *)str, result, &pars));
}

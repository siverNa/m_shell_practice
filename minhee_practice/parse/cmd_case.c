#include "../minishell_prec.h"

int	word_len(const char *str, int i, char c)
{
	int		w_len;

	w_len = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		w_len++;
	}
	return (w_len);
}

void	case_double_q(char *str, char **result, t_pars *pars)
{
	int		w_len;

	pars->i++;
	w_len = word_len(str, pars->i, 34);
	result[pars->j] = (char *)malloc(sizeof(char) * w_len + 1);
	if (!result)
		return ;
	while (str[pars->i] != '\0' && str[pars->i] != 34)
		result[pars->j][pars->count++] = str[pars->i++];
}

void	case_single_q(char *str, char **result, t_pars *pars)
{
	int		w_len;

	pars->i++;
	w_len = word_len(str, pars->i, 39);
	result[pars->j] = (char *)malloc(sizeof(char) * w_len + 1);
	if (!result)
		return ;
	while (str[pars->i] != '\0' && str[pars->i] != 39)
		result[pars->j][pars->count++] = str[pars->i++];
}

void	case_space(char *str, char **result, t_pars *pars)
{
	int		w_len;

	w_len = word_len(str, pars->i, ' ');
	result[pars->j] = (char *)malloc(sizeof(char) * w_len + 1);
	if (!result)
		return ;
	while (str[pars->i] != '\0' && str[pars->i] != ' ')
		result[pars->j][pars->count++] = str[pars->i++];
}

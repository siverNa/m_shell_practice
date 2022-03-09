#include "../minishell_prec.h"

int	parse_token(t_token *token, char *str, int *j, char **env)
{
	while (str[*j] == ' ')
		(*j)++;
	if (str[*j] == '|')
	{
		concat_char(&(token->value), '|');
		(*j)++;
		return (1);
	}
	if (str[*j] == '<' || str[*j] == '>')
	{
		*j = process_redir(str, *j, &(token->value), env);
		return (2);
	}
	while (str[*j] && str[*j] != ' ' && str[*j] != '|')
	{
		if (str[*j] == '\"')
			*j = process_dquote(str, *j, &(token->value), env);
		else if (str[*j] == '\'')
			*j = process_squote(str, *j, &(token->value));
		else if (str[*j] == '$')
			*j = process_env(str, *j, &(token->value), env);
		else
			concat_char(&(token->value), str[(*j)++]);
	}
	return (0);
}

void	handle_count(int *status, int flag, int *count)
{
	if (*status == 0)
	{
		if (flag == 1)
		{
			*status = 1;
			*count = *count + 1;
		}
	}
	else
	{
		if (flag == 0)
			*status = 0;
	}
	return ;
}

int	count_tokens(char *str)
{
	int	count;
	int	i;
	int	status;

	count = 0;
	status = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			handle_count(&status, 0, &count);
		else if (str[i] == '|')
		{
			count++;
			status = 0;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			count++;
			status = 0;
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				i++;
		}
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i = check_quote(str, i, str[i]);
			handle_count(&status, 1, &count);
		}
		else
			handle_count(&status, 1, &count);
		i++;
	}
	return (count);
}

t_token	*tokenize(char *str, char **env)
{
	t_token	*ret;
	int		count;
	int		i;
	int		j;

	count = count_tokens(str);
	ret = (t_token *)malloc(sizeof(t_token) * (count + 1));
	if (!ret)
	{
		free(str);
		exit(1);
	}
	ret[count].value = NULL;
	ret[count].type = -1;
	i = 0;
	j = 0;
	while (i < count)
	{
		ret[i].value = NULL;
		ret[i].type = parse_token(&ret[i], str, &j, env);
		i++;
	}
	return (ret);
}

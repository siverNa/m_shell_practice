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
	int	i;
	int	size;

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

int	process_env(char *str, int j, char **token, char **env)
{
	char	*var_name;
	char	*value;
	int		k;

	j++;
	var_name = NULL;
	if (str[j] == 0 || str[j] == ' ')
	{
		concat_char(token, '$');
		return(j);
	}
	while (ft_isalpha(str[j]) || str[j] == '_')
	{
		concat_char(&var_name, str[j]);
		j++;
	}
	value = find_value(var_name, env);
	k = 0;
	while(value[k])
	{
		concat_char(token, value[k]);
		k++;
	}
	free(var_name);
	return (j);
}

int	process_dquote(char *str, int j, char **token, char **env)
{
	int	k;

	k = check_quote(str, j, str[j]);
	if (k == j)
	{
		concat_char(token, str[j]);
		return (j + 1);
	}
	j++;
	while (j < k)
	{
		if (str[j] == '$')
		{
			j = process_env(str, j, token, env);
		}
		else
		{
			concat_char(token, str[j]);
			j++;
		}
	}
	j++;
	return (j);
}

int	process_squote(char *str, int j, char **token)
{
	int	k;

	k = check_quote(str, j, str[j]);
	if (k == j)
	{
		concat_char(token, str[j]);
		return (j + 1);
	}
	j++;
	while (j < k)
	{
		concat_char(token, str[j]);
		j++;
	}
	j++;
	return (j);
}

int	process_redir(char *str, int j, char **token, char **env)
{
	if (str[j] == '<')
	{
		concat_char(token, '<');
		j++;
		if (str[j] == '<')
		{
			concat_char(token, '<');
			j++;
		}
		return (j);
	}
	else
	{
		concat_char(token, '>');
		j++;
		if (str[j] == '>')
		{
			concat_char(token, '>');
			j++;
		}
		return (j);
	}
}

void	parse_token(t_token *token, char *str, int *j, char **env)
{
	token->value = NULL;
	while (str[*j] == ' ')
		(*j)++;
	if (str[*j] == '|')
	{
		concat_char(&(token->value), '|');
		(*j)++;
		token->type = 1;
		return ;
	}
	if (str[*j] == '<' || str[*j] == '>')
	{
		*j = process_redir(str, *j, &(token->value), env);
		token->type = 2;
		return ;
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
		{
			concat_char(&(token->value), str[*j]);
			(*j)++;
		}
	}
	token->type = 0;
	return ;
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
	int	count;
	int	i;
	int	j;

	count = count_tokens(str);
	ret = (t_token *)malloc(sizeof(t_token ) * (count + 1));
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
		parse_token(&ret[i], str, &j, env);
		i++;
	}
	//free(str);
	return (ret);
}

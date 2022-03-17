#include "../minishell_prec.h"

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
		return (j);
	}
	if (str[j] == '?')
		return (get_exit_status(token, j));
	while (ft_isalnum(str[j]) || str[j] == '_')
		concat_char(&var_name, str[j++]);
	if (var_name == NULL)
	{
		*token = ft_strdup("");
		return (j);
	}
	get_env_token(token, env, var_name);
	free(var_name);
	return (j);
}

int	process_env_quote(char *str, int j, char **token, char **env)
{
	char	*var_name;
	char	*value;
	int		k;

	j++;
	var_name = NULL;
	if (str[j] == 0 || str[j] == ' ')
	{
		concat_char(token, '$');
		return (j);
	}
	while (ft_isalnum(str[j]) || str[j] == '_')
		concat_char(&var_name, str[j++]);
	if (var_name == NULL)
	{
		concat_char(token, '$');
		return (j);
	}
	value = find_value(var_name, env);
	k = 0;
	while (value[k])
		concat_char(token, value[k++]);
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
			j = process_env_quote(str, j, token, env);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:27:20 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/17 15:51:35 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_prec.h"

int	process_env(char *str, int j, char **token, char **env)
{
	char	*var_name;

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

int	process_redir(char *str, int j, char **token)
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

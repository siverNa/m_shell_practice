#include "../minishell_prec.h"

void	add_export(char *str, char **new, int i)
{
	printf("cmd_line : %s, i : %d\n", str, i);
	new[i] = ft_strdup(str);//메모리 누수 예상지점2
	new[i + 1] = NULL;
	printf("new[%d] : %s, %p\n", i, new[i], new[i]);
}
/*
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
			free((*envs)[i]);
			(*envs)[i] = ft_strdup(str);
			return (1);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));//메모리누수 예상지점1
	if (!new)
		return (-1);
	i = -1;
	while ((*envs)[++i])
	{
		new[i] = ft_strdup((*envs)[i]);//메모리 누수 예상 지점3
		free((*envs)[i]);
	}
	add_export(str, new, i);
	free(*envs);//이건 맞는 free
	*envs = new;
	return (1);
}*/

int	isvalid_export(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	print_export(char **envs)
{
	int		i;

	i = 0;
	while (envs[i])
	{
		ft_putstr_fd(envs[i], STDOUT);
		write(STDOUT, "\n", 1);
		i++;
	}
}
/*
void	built_export(t_node *cmd, char **cmd_line, t_data *input)
{
	int		i;
	int		res;
	char	**temp;

	i = 0;
	res = 0;
	temp = cmd_line;
	if (cmd->pre_status == 1)
		return ;
	if (arr_2dchar_len(cmd_line) == 1)
		print_export(input->env);
	else
	{
		remove_char(cmd_line[1], '\'');
		while (cmd_line[++i])
		{
			if (isvalid_export(ft_strtok(temp[i], '=')) == FALSE)
			{
				print_identify_error_msg("export", temp[i]);
				g_exit_status = 1;
			}
			remove_char(cmd_line[i], '$');
			res = check_export(cmd_line[i], &input->env);
		}
	}
	if (res != 1)
		g_exit_status = 1;
}*/

int	check_env(char *str, char *envs)
{
	int		i;

	i = 0;
	while (str[i] && envs[i] && (str[i] == envs[i]) && (str[i] != '=')
		&& (envs[i] != '='))
		i++;
	if (i == 0)
		return (0);
	if (((envs[i] == '=') && (str[i] == '='))
		|| ((envs[i] == '=') || str[i] == 0))
		return (1);
	return (0);
}

int	start_export(char *cmd_line, char ***c_envs)
{
	int		i;
	char	**new;

	if (cmd_line[0] == '=' || cmd_line[0] == '\0')
		return (ERROR);
	i = -1;
	while ((*c_envs)[++i] != NULL)
	{
		if (check_env(cmd_line, (*c_envs)[i]))
		{
			free((*c_envs)[i]);
			(*c_envs)[i] = ft_strdup(cmd_line);
			return (SUCCESS);
		}
	}
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (ERROR);
	i = -1;
	while ((*c_envs)[++i])
	{
		new[i] = ft_strdup((*c_envs)[i]);
		free((*c_envs)[i]);
	}
	printf("cmd_line : %s, i = %d\n", cmd_line, i);
	add_export(cmd_line, new, i);
	printf("old c_envs addr : %p, new addr : %p\n", *c_envs, new);
	free(*c_envs);
	(*c_envs) = new;
	printf("new c_envs addr : %p\n", *c_envs);
	return (SUCCESS);
}

//int	built_export(char **cmd_line, char **c_envs)
int	built_export(char **cmd_line, t_data *input)
{
	int		i;
	int		res;

	i = 0;
	res = 1;
	if (arr_2dchar_len(cmd_line) == 1)
		print_export(input->env);
	else
	{
		while (cmd_line[++i])
		{
			if (start_export(cmd_line[i], &input->env))
				;
			else
				res = 0;
		}
	}
	if (res)
		return (1);
	else
		return (0);
}

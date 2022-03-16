#include "../minishell_prec.h"

void	add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

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
	int		size;
	char	**temp;

	i = 0;
	size = 0;
	while (envs[size])
		size++;
	temp = (char **)malloc(sizeof(char *) * (size + 1));
	sort_envs(temp, envs, size);
	while (temp[i])
	{
		ft_putstr_fd(temp[i], STDOUT);
		write(STDOUT, "\n", 1);
		i++;
	}
	free_2d_arr(temp);
}

int	start_export(char *cmd_line, char ***c_envs)
{
	int		i;
	char	**new;

	if (cmd_line[0] == '=' || cmd_line[0] == '\0' || ft_strlen(cmd_line) == 1)
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
	copy_env_to_new(new, c_envs, &i);
	add_export(cmd_line, new, i);
	free(*c_envs);
	(*c_envs) = new;
	return (SUCCESS);
}

void	built_export(t_node *cmd, char **cmd_line, t_data *input)
{
	int		i;
	int		res;

	i = 0;
	res = 1;
	if (cmd->pre_status == 1)
		return ;
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
		g_exit_status = 0;
	else
		g_exit_status = 1;
}

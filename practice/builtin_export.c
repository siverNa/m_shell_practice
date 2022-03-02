#include "minishell_prec.h"

void	add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

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
			(*envs)[i] = ft_strdup(str);
			return (1);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (-1);
	i = -1;
	while ((*envs)[++i])
		new[i] = ft_strdup((*envs)[i]);
	add_export(str, new, i);
	//free_2d_arr(*envs);
	*envs = new;
	return (1);
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

	i = 0;
	while (envs[i])
	{
		ft_putstr_fd(envs[i], STDIN);
		write(STDOUT, "\n", 1);
		i++;
	}
}

void	built_export(t_node *cmd, char **cmd_line)
{
	int		i;
	int		res;
	char	**temp;

	i = 0;
	res = 0;
	temp = cmd_line;
	if (arr_2dchar_len(cmd_line) == 1)
		print_export(cmd->c_envs);
	else
	{
		remove_char(cmd_line[1], '\'');
		while (cmd_line[++i])
		{
			if (isvalid_export(ft_strtok(temp[i], '=')) == FALSE)
			{
				print_identify_error_msg("export", temp[i]);
			}
			remove_char(cmd_line[i], '$');
			res = check_export(cmd_line[i], &cmd->c_envs);
		}
	}
}

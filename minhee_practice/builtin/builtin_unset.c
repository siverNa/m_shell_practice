#include "../minishell_prec.h"

int	isvalid_env(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_isalnum(line[i]) || line[i] == '_')
			;
		else
			return (FALSE);
	}
	if (!i)
		return (FALSE);
	return (TRUE);
}

int	check_key_value(char *line, char *envs)
{
	int	i;

	i = 0;
	while (line[i] && envs[i] && (line[i] == envs[i]) && (envs[i] != '='))
		i++;
	if ((line[i] == '\0') && (envs[i] == '='))
		return (TRUE);
	return (FALSE);
}

int	env_unset(char *line, char ***envs)
{
	int	i;
	int	last;

	last = 0;
	while (((*envs)[last]) != NULL)
		last++;
	if (last < 1)
		return (ERROR);
	i = -1;
	while (((*envs)[++i]) != NULL)
	{
		if (check_key_value(line, (*envs)[i]))
		{
			free((*envs)[i]);
			(*envs)[i] = ft_strdup((*envs)[last - 1]);
			free((*envs)[last - 1]);
			(*envs)[last - 1] = NULL;
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}

void	built_unset(t_node *cmd, char **cmd_line, t_data *input)
{
	int	i;
	int	res;

	i = 1;
	res = 0;
	if (cmd->pre_status == 1)
		return ;
	while (cmd_line[i])
	{
		remove_char(cmd_line[i], '\'');
		res = isvalid_env(cmd_line[i]) && env_unset(cmd_line[i], &input->env);
		i++;
	}
	if (res != 1)
		g_exit_status = 1;
}

#include "minishell_prec.h"

void	free_2d_arr(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	catch_env_to_path(t_node *cmd, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			cmd->temp_path = env[i] + 5;
		i++;
	}
}

char	*build_path(t_node *cmd, char *cmd_line, char **env)
{
	char	**split_path;
	char	*join1;
	char	*join2;
	int		i;

	i = 0;
	if (!ft_strncmp(cmd_line, "/", 1))
		return (cmd_line);
	catch_env_to_path(cmd, env);
	split_path = ft_split(cmd->temp_path, ':');
	while (split_path[i])
	{
		join1 = ft_strjoin(split_path[i], "/");
		join2 = ft_strjoin(join1, cmd_line);
		free(join1);
		if (open(join2, O_RDONLY) >= 0)
		{
			free_2d_arr(split_path);
			return (join2);
		}
		free(join2);
		i++;
	}
	free_2d_arr(split_path);
	return (NULL);
}
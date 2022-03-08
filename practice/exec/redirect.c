#include "../minishell_prec.h"

void	set_redir_fd(char *redir, char *filename, int *fd_in, int *fd_out)
{
	if (ft_strcmp(redir, ">"))
	{
		if (*fd_out != 1)
			close(*fd_out);
		*fd_out = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (ft_strcmp(redir, ">>"))
	{
		if (*fd_out != 1)
			close(*fd_out);
		*fd_out = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (ft_strcmp(redir, "<"))
	{
		if (*fd_in != 0)
			close(*fd_in);
		*fd_in = open(filename, O_RDONLY);
	}
	else
		;
	//<<: read from input until delimiter
}

int	redirect(t_data *input, t_cmd *cmd)
{
	int	x;
	int	y;
	char	*redir;
	char	*filename;

	x = cmd->start;
	y = cmd->last;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	while (x <= y)
	{
		if (input->tokens[x].type == 2)
		{
			redir = tokens[x].value;
			filename = tokens[x + 1].value;
			set_redir_fd(redir, filename, &(cmd->fd_in), &(cmd->fd_out));
		}
		x++;
	}
	if (cmd->fd_out == -1 || cmd->fd_in == -1)
		return (0);
	return (1);
}

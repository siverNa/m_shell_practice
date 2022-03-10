#include "../minishell_prec.h"

void	open_filename(char *redir, char *filename, int *fd_in, int *fd_out)
{
	if (ft_strcmp(redir, ">"))
		*fd_out = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ft_strcmp(redir, ">>"))
		*fd_out = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (ft_strcmp(redir, "<"))
		*fd_in = open(filename, O_RDONLY);
	else
	{
		//<< (heredocument) read from stdin until delimiter(=filename) is found
		//step1. create a temporary file
		//step2. readline -> write to temporary file line by line
		//step3. if the line == delimiter, stop writing
		//step4. set fd_in to the file created
		//*fd_in = here_doc();
	}
}

int	set_fd_in_out(t_data *input, t_node *cmd)
{
	int	x;
	int	y;
	char	*redir;
	char	*filename;

	x = cmd->start;
	y = cmd->last;
	printf("tokens: from [%d] to [%d]\n", x, y);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	while (x <= y)
	{
		if (input->tokens[x].type == 2)
		{
			redir = input->tokens[x].value;
			printf("redir: [%s]\n", redir);
			filename = input->tokens[x + 1].value;
			printf("filename: [%s]\n", filename);
			open_filename(redir, filename, &(cmd->fd_in), &(cmd->fd_out));
		}
		x++;
	}
	if (cmd->fd_out == -1 || cmd->fd_in == -1)
		return (0);
	return (1);
}

void	redirect(t_data *input, t_node *cmd)
{
	if (set_fd_in_out(input, cmd) == 0)
		return ;
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT);
		close(cmd->fd_out);
	}
	return ;
}

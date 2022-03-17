/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhekim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:27:50 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/17 14:27:52 by minhekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_prec.h"

int	here_doc(char *delim, t_node *cmd)
{
	int		fd;
	char	*buf;

	cmd->here_doc = 1;
	fd = open(".temp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	buf = readline(">");
	while (buf != NULL && ft_strcmp(buf, delim) != 1)
	{
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
		buf = readline(">");
	}
	free(buf);
	close(fd);
	fd = open(".temp", O_RDONLY);
	return (fd);
}

void	open_filename(char *redir, char *filename, t_node *cmd)
{
	if (ft_strcmp(redir, ">"))
		cmd->fd_out = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ft_strcmp(redir, ">>"))
		cmd->fd_out = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (ft_strcmp(redir, "<"))
		cmd->fd_in = open(filename, O_RDONLY);
	else
		cmd->fd_in = here_doc(filename, cmd);
}

int	set_fd_in_out(t_data *input, t_node *cmd)
{
	int		x;
	int		y;
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
			redir = input->tokens[x].value;
			filename = input->tokens[x + 1].value;
			open_filename(redir, filename, cmd);
			if (cmd->fd_out == -1 || cmd->fd_in == -1)
			{
				ft_putstr_fd("-bash: error: No such file or directory\n", 1);
				return (0);
			}
		}
		x++;
	}
	return (1);
}

int	redirect(t_data *input, t_node *cmd)
{
	if (set_fd_in_out(input, cmd) == 0)
		return (-1);
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
	return (0);
}

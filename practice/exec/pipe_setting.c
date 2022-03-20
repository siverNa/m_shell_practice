/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 01:49:42 by sna               #+#    #+#             */
/*   Updated: 2022/03/20 22:52:12 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

int	is_pipe(t_node **cmd, t_node **n_cmd)
{
	if ((*cmd)->next == NULL)
		return (ERROR);
	(*n_cmd) = (*cmd)->next;
	(*n_cmd)-> pre_status = 1;
	if (pipe((*n_cmd)->fd) == -1)
	{
		print_error_msg("pipe", "pipe error");
		exit(1);
	}
	return (SUCCESS);
}

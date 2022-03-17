/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:34:41 by sna               #+#    #+#             */
/*   Updated: 2022/03/17 15:47:49 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_prec.h"

int	g_exit_status = 0;

void	free_cmdline(char **cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		free(cmdline[i]);
		cmdline[i] = NULL;
		i++;
	}
	free(cmdline);
	cmdline = NULL;
}

void	shell_ready(t_data *input, t_node *cmds, t_node *list)
{
	input->tokens = tokenize(input->str, input->env);
	if (check_syntax(input) == -1)
	{
		add_history(input->str);
		free(input->str);
		free_tokens(input->tokens);
		return ;
	}
	list = parse(input->tokens);
	cmds = list;
	process(cmds, input);
	add_history(input->str);
	free(input->str);
	free_tokens(input->tokens);
	free_cmds_list(list);
	list = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data			input;
	t_node			*cmds;
	t_node			*list;

	setting_signal();
	(void)ac;
	(void)av;
	input.env = NULL;
	input.env = copy_envs(env);
	list = NULL;
	cmds = NULL;
	while (1)
	{
		input.str = readline("\033[34;1mminishell : \033[0m");
		if (!(input.str))
			input_ctrld_exit();
		else if (*(input.str) == '\0')
			free(input.str);
		else
			shell_ready(&input, list, cmds);
	}
	free_2d_arr(input.env);
	return (g_exit_status & 255);
}

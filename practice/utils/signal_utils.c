/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:27:01 by sna               #+#    #+#             */
/*   Updated: 2022/03/20 22:49:19 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	setting_signal(void)
{
	struct termios	org_term;
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &org_term);
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		print_errno(NULL, 1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_errno(NULL, 1);
}

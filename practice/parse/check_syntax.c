/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhekim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:26:50 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/17 14:26:53 by minhekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhekim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:26:48 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/17 14:26:48 by minhekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_prec.h"

int	check_word(t_token *tokens, int i)
{
	while (tokens[i].type == 0)
		i++;
	return (i);
}

int	check_pipe(t_token *tokens, int i)
{
	if (i != 0 && tokens[i + 1].type == 0)
		return (i + 1);
	if (i != 0 && tokens[i + 1].type == 2)
		return (i + 1);
	ft_putstr_fd("-bash: syntax error near unexpected token \'", 1);
	ft_putstr_fd(tokens[i].value, 1);
	write(1, "\'\n", 2);
	return (-1);
}

int	check_redir(t_token *tokens, int i)
{
	i++;
	if (tokens[i].type == 0)
		return (i);
	ft_putstr_fd("-bash: syntax error near unexpected token \'", 1);
	ft_putstr_fd(tokens[i - 1].value, 1);
	write(1, "\'\n", 2);
	return (-1);
}

int	check_syntax(t_data *input)
{
	int	i;

	i = 0;
	while (input->tokens[i].type != -1)
	{
		if (input->tokens[i].type == 0)
			i = check_word(input->tokens, i);
		else if (input->tokens[i].type == 1)
			i = check_pipe(input->tokens, i);
		else if (input->tokens[i].type == 2)
			i = check_redir(input->tokens, i);
		else
			i = -1;
		if (i == -1)
		{
			g_exit_status = 2;
			return (-1);
		}
	}
	return (0);
}

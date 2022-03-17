/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:33:34 by minhekim          #+#    #+#             */
/*   Updated: 2022/03/17 15:22:20 by sna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PREC_H
# define MINISHELL_PREC_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# define TRUE		1
# define FALSE		0

# define STDIN		0
# define STDOUT		1
# define STDERR		2

# define SUCCESS	1
# define ERROR		-1

extern int			g_exit_status;

typedef struct s_node
{
	char			**cmd_line;
	char			*file_path;
	char			*temp_path;
	char			**c_envs;
	int				fd[2];
	int				fd_in;
	int				fd_out;
	int				status;
	int				pre_status;
	int				redir;
	int				here_doc;
	int				start;
	int				last;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_token
{
	char	*value;
	int		type;
}			t_token;

typedef struct s_data
{
	char	*str;
	t_token	*tokens;
	char	**env;
}			t_data;

typedef struct s_pars
{
	int				i;
	int				j;
	int				count;
	int				len;
}					t_pars;

/*
**	main.c
*/
void	free_cmdline(char **cmdline);
void	shell_ready(t_data *input, t_node *cmds, t_node *list);

/*
**	prec_process.c
*/
void	free_struct(t_node *cmd);
void	child_process(t_node *cmd, t_data *input, char *str, t_node *n_cmd);
int		start_pipe(t_node *cmd, t_data *input, char *str);
void	process(t_node *cmd, t_data *input, char *str);

/*
** redirect.c
*/
int		redirect(t_data *input, t_node *cmd);
int		set_fd_in_out(t_data *input, t_node *cmd);

/*
** cmd_init.c
*/
char	**parsing_str(char *str, char **result, t_pars *pars);
void	count_word(const char *str, int *i, int *count);
int		count_str(const char *str);
char	**cmd_init(const char *str);

/*
** cmd_case.c
*/
int		word_len(const char *str, int i, char c);
void	case_double_q(char *str, char **result, t_pars *pars);
void	case_single_q(char *str, char **result, t_pars *pars);
void	case_space(char *str, char **result, t_pars *pars);

/*
** cmd_build_path.c
*/
void	free_2d_arr(char **str);
void	catch_env_to_path(t_node *cmd, t_data *input);
char	*build_path(t_node *cmd, t_data *input, char *cmd_line);

/*
** builtin.c
*/
int		check_builtin(char **cmd_line);
int		start_builtin(t_node *cmd, char **cmd_line, t_data *input);
int		remove_char(char *str, char c);

/*
** builtin_cd.c
*/
int		built_cd(char **cmd_line, char **c_envs);
int		start_cd(char *input, char **c_envs);
void	set_cd_pwd(char *ch_path, char *old_pwd, char *path, char **c_envs);

/*
** builtin_pwd.c
*/
void	built_pwd(void);

/*
** builtin_env.c
*/
void	built_env(char **c_envs);

/*
** builtin_export.c
*/
void	add_export(char *str, char **new, int i);
int		isvalid_export(char *input);
void	print_export(t_data *input);
int		start_export(char *cmd_line, char ***c_envs);
void	built_export(t_node *cmd, char **cmd_line, t_data *input);

/*
** builtin_echo.c
*/
void	echo_exit_status(void);
void	echo_envs(char **cmd_line, char **envs, int i);
int		is_option_n(char *str);
void	built_echo(char **cmd_line, char **envs);

/*
** builtin_unset.c
*/
int		isvalid_env(char *line);
int		check_key_value(char *line, char *envs);
int		env_unset(char *line, char ***envs);
void	built_unset(t_node *cmd, char **cmd_line, t_data *input);

/*
** builtin_exit.c
*/
int		isdigit_str(char *str);
void	start_exit(void);
void	built_exit(t_node *cmd, char **cmd_line);

/*
** error_execute.c
*/
int		print_exe_error_msg(t_node *cmd, char *str);
int		print_error_msg(char *input, char *err_msg);
int		print_error_msg_2(char *first, char *sec, char *err_msg);
void	print_identify_error_msg(char *first, char *sec);

/*
** env_util.c
*/
char	**copy_envs(char **envs);
char	*find_value(char *input, char **envs);
int		arr_2dchar_len(char **str);
int		check_env(char *str, char *envs);
void	copy_env_to_new(char **new, char ***c_envs, int *i);

/*
** free.c
*/
void	free_node_cmdline(t_node *node);
void	free_cmds_list(t_node *list);
void	free_tokens(t_token *token);

/*
** tokenize.c
*/
t_token	*tokenize(char *str, char **env);
int		count_tokens(char *str);
void	handle_count(int *status, int flag, int *count);
int		parse_token(t_token *token, char *str, int *j, char **env);

/*
** tokenize_process.c
*/
int		process_redir(char *str, int j, char **token, char **env);
int		process_squote(char *str, int j, char **token);
int		process_dquote(char *str, int j, char **token, char **env);
int		process_env(char *str, int j, char **token, char **env);

/*
** tokenize_utils.c
*/
void	get_env_token(char **token, char **env, char *var_name);
int		get_exit_status(char **token, int j);
void	concat_char(char **str, char c);
int		check_quote(char *str, int i, char quote);

/*
** parse.c
*/
t_node	*parse(t_token *tokens);

/*
 ** check_syntax.c
*/
int		check_syntax(t_data *input);

/*
** utils.c
*/
int		get_cmdline_len(char **cmdline);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp2(const char *s1, const char *s2);
void	input_ctrld_exit(void);
void	receive_child_status(int status);

/*
** sort_envs.c
*/
void	sort_envs(char **temp, t_data *input, int size);

/*
** signal_utils.c
*/
void	sig_handler2(int signum);
void	sig_handler(int signum);
void	setting_signal(void);

#endif

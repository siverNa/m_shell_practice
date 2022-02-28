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

typedef struct s_node
{
	char			**cmd_line;
	char			*file_path;
	char			*temp_path;
	char			**c_envs;
	int				fd[2];
	int				status;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_pars
{
	int				i;
	int				j;
	int				count;
	int				len;
}					t_pars;

/*
typedef struct		s_deq
{
	int				size;
	t_node			*head;
	t_node			*tail;
}					t_deq;
*/

/*
** deque_func.c
*/
/*void	free_cmdline(char **cmdline);
void	free_deq(t_deq *cmd);
void	init_cmd(t_deq *deq);
int		dq_is_empty(t_deq *d);
void	lst_addend(t_deq *deq, char *str);
void	insert_str(t_deq *deq, char *str);
*/

/*
**	main.c
*/
void	free_cmdline(char **cmdline);
void	sig_handler(int signum);
void	setting_signal(void);

/*
**	prec_process.c
*/
void	free_struct(t_node *cmd, char *str);
void	child_process(t_node *cmd, char *str);
void	process(t_node *cmd, char *str);
void	start_process(t_node *cmd);

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
void	catch_env_to_path(t_node *cmd);
char	*build_path(t_node *cmd, char *cmd_line);

/*
** builtin.c
*/
int		check_builtin(char **cmd_line);
int		start_builtin(t_node *cmd, char **cmd_line);
int		remove_char(char *str, char c);

/*
** builtin_cd.c
*/
int		exec_cd_home(char *path, char **cmd_line, char **c_envs);
int		exec_cd_envs(char *path, char **cmd_line, char **c_envs);
void	set_pwd(char **c_envs);
void	built_cd(char **cmd_line, char **envs);

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
int		check_export(char *str, char ***envs);
int		isvalid_export(char *input);
void	print_export(char **envs);
void	built_export(t_node *cmd, char **cmd_line);

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
void	built_unset(t_node *cmd, char **cmd_line);

/*
** error_execute.c
*/
int		print_error_msg(char *input, char *err_msg);
int		print_error_msg_2(char *first, char *sec, char *err_msg);
void	print_identify_error_msg(char *first, char *sec);

/*
** env_util.c
*/
char	**copy_envs(char **envs);
char	*find_value(char *input, char **envs);
int		arr_2dchar_len(char **str);
char	*ft_strtok(char *str, char c);

#endif
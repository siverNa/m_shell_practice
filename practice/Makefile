NAME =		minishell_prec

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
LIBFT =		-L../libft -lft
READLINE =	-lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include

SRCS =		prec_main.c prec_process.c cmd_init.c cmd_case.c cmd_build_path.c \
			builtin.c builtin_cd.c builtin_pwd.c builtin_env.c builtin_export.c \
			builtin_echo.c builtin_unset.c builtin_exit.c \
			env_util.c error_execute.c

OBJS =		$(SRCS:.c=.o)

$(NAME) :	$(OBJS) $(READLINE)
			@$(MAKE) bonus -C ../libft
			$(CC) $^ -I . $(READLINE) $(LIBFT) -o $@

all :		$(NAME)

clean :
			rm -rf $(OBJS)
			@$(MAKE) CLEAN -C ../libft

fclean :	clean
			rm -f $(OBJS)
			@$(MAKE) fclean -C ../libft

re :		fclean all

.PHONY :	all clean fclean re
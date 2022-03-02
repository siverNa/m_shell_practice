NAME =		minishell_prec

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
LIBFT =		-L../libft -lft
READLINE =	-lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include
G3 =		-g3 -fsanitize=address

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	READLINE =	-lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include
endif
ifeq ($(UNAME_S),DARWIN)
	READLINE =	-lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
endif

SRCS =		prec_main.c prec_process.c cmd_init.c cmd_case.c cmd_build_path.c \
			builtin.c builtin_cd.c builtin_pwd.c builtin_env.c builtin_export.c \
			builtin_echo.c builtin_unset.c builtin_exit.c \
			env_util.c error_execute.c

OBJS =		$(SRCS:.c=.o)

$(NAME) :	$(OBJS)
			@$(MAKE) bonus -C ../libft
			$(CC) $^ -I . $(READLINE) $(LIBFT) -o $@ $(G3)

%.o:		%.c
			$(CC) -c $^ -o $@ $(READLINE)

all :		$(NAME)

clean :
			rm -rf $(OBJS)
			@$(MAKE) clean -C ../libft

fclean :	clean
			rm -f $(NAME)
			@$(MAKE) fclean -C ../libft

re :		fclean all

.PHONY :	all clean fclean re
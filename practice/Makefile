NAME =		minishell_prec

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
LIBFT =		-L../libft -lft
G3 =		-g3 -fsanitize=address

COMPILE_FLAG = -lreadline -L/$(HOME)/.brew/opt/readline/lib
OBJ_FLAG = -I/$(HOME)/.brew/opt/readline/include
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	COMPILE_FLAG = -lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib
	OBJ_FLAG = -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include
endif

SRCS =		prec_main.c exec/prec_process.c parse/cmd_init.c parse/cmd_case.c parse/cmd_build_path.c \
			builtin/builtin.c builtin/builtin_cd.c builtin/builtin_pwd.c builtin/builtin_env.c builtin/builtin_export.c \
			builtin/builtin_echo.c builtin/builtin_unset.c builtin/builtin_exit.c \
			utils/env_util.c exec/error_execute.c \
			utils/free.c parse/parse.c parse/tokenize.c utils/utils.c

OBJS =		$(SRCS:.c=.o)

$(NAME) :	$(OBJS)
			@$(MAKE) bonus -C ../libft
			$(CC) $^ -I . $(COMPILE_FLAG) $(LIBFT) -o $@ $(G3)

%.o:		%.c
			$(CC) -c $^ -o $@ $(OBJ_FLAG)

all :		$(NAME)

clean :
			rm -rf $(OBJS)
			@$(MAKE) clean -C ../libft

fclean :	clean
			rm -f $(NAME)
			@$(MAKE) fclean -C ../libft

re :		fclean all

.PHONY :	all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sna <sna@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 14:37:01 by sna               #+#    #+#              #
#    Updated: 2022/03/17 15:35:44 by sna              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
LIBFT =		-L./libft -lft
G3 =		-g3 -fsanitize=address

COMPILE_FLAG = -lreadline -L/$(HOME)/.brew/opt/readline/lib
OBJ_FLAG = -I/$(HOME)/.brew/opt/readline/include
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	COMPILE_FLAG = -lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib
	OBJ_FLAG = -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include
endif

SRCS =		prec_main.c src/exec/prec_process.c src/parse/cmd_init.c src/parse/cmd_case.c src/parse/cmd_build_path.c \
			src/builtin/builtin.c src/builtin/builtin_cd.c src/builtin/builtin_pwd.c src/builtin/builtin_env.c \
			src/builtin/builtin_export.c src/builtin/builtin_echo.c src/builtin/builtin_unset.c src/builtin/builtin_exit.c \
			src/utils/env_util.c src/utils/sort_envs.c src/utils/signal_utils.c src/exec/error_execute.c \
			src/utils/free.c src/parse/parse.c src/parse/tokenize.c src/parse/check_syntax.c src/utils/utils.c \
			src/parse/tokenize_utils.c src/parse/tokenize_process.c src/exec/redirect.c

OBJS =		$(SRCS:.c=.o)

$(NAME) :	$(OBJS)
			@$(MAKE) bonus -C ./libft
			$(CC) $(CFLAGS) $^ -I . $(COMPILE_FLAG) $(LIBFT) -o $@

%.o:		%.c
			$(CC) $(CFLAGS) -c $^ -o $@ $(OBJ_FLAG)

all :		$(NAME)

clean :
			rm -rf $(OBJS)
			@$(MAKE) clean -C ./libft

fclean :	clean
			rm -f $(NAME)
			@$(MAKE) fclean -C ./libft

re :		fclean all

.PHONY :	all clean fclean re

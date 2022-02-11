NAME =		minishell_prec

CC =		gcc
LIBFT =		-L../libft -lft
READLINE =	-lreadline -L/Users/minhekim/.brew/opt/readline/lib -I/Users/minhekim/.brew/opt/readline/include

SRCS =		prec_main.c practice_exec.c

OBJS =		$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/Users/minhekim/.brew/opt/readline/include -c $< -o $@

$(NAME) :	$(OBJS)
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

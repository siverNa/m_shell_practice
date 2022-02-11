NAME =		minishell_prec

CC =		gcc
LIBFT =		-L../libft -lft
READLINE =	-lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include

SRCS =		prec_main.c

OBJS =		$(SRCS:.c=.o)

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
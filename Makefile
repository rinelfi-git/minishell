NAME = minishell
CC = cc
CARG = -Werror -Wextra -Wall
SRCs = src/main.c \
		src/builtins/builtin.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/core/cmd_args.c \
		src/core/cmd_fd.c \
		src/core/cmd_path.c \
		src/core/env.c \
		src/core/exec.c \
		src/core/heredoc.c \
		src/core/cmd.c \
		src/core/init.c \
		src/core/list_cmd.c \
		src/core/list_token.c \
		src/core/prompt.c \
		src/core/signal.c \
		src/core/token.c \
		src/utils/free.c \
		src/utils/is.c \
		src/utils/quote.c \
		src/utils/string.c
OBJs = $(SRCs:.c=.o)
INCs = -Iinclude \
		-Ilibs/libft
LIBs = -Llibs/libft -lft \
		-lreadline
FT = libs/libft/libft.a

$(NAME) : $(OBJs) $(FT)
	$(CC) $(CARG) $(OBJs) $(LIBs) -o $@

$(FT) :
	make -C libs/libft

all : $(NAME)

clean :
	rm -rf $(OBJs)
	rm -rf libs/libft/*.o

fclean : clean
	rm -rf $(NAME)
	rm -rf libs/libft/libft.a

re : fclean all

%.o : %.c
	$(CC) $(CARG) $(INCs) -c $< -o $@

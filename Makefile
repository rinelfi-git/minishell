NAME = minishell
CC = cc
CARG = -Werror -Wextra -Wall
SRCs = src/main.c \
		src/core/builtins/builtin.c \
		src/core/builtins/cd.c \
		src/core/builtins/echo.c \
		src/core/builtins/env.c \
		src/core/builtins/exit.c \
		src/core/builtins/export.c \
		src/core/builtins/export_operation.c \
		src/core/builtins/pwd.c \
		src/core/builtins/unset.c \
		src/core/cmd/cmd_args.c \
		src/core/cmd/cmd_fd.c \
		src/core/cmd/cmd_path.c \
		src/core/cmd/cmd.c \
		src/core/cmd/list_cmd.c \
		src/core/signal/heredoc.c \
		src/core/signal/signal.c \
		src/core/token/list_token.c \
		src/core/token/token.c \
		src/core/env.c \
		src/core/env2.c \
		src/core/exec.c \
		src/core/exec2.c \
		src/core/expand.c \
		src/core/heredoc.c \
		src/core/init.c \
		src/core/parse.c \
		src/core/prompt.c \
		src/core/syntax_check.c \
		src/utils/error_message.c \
		src/utils/is.c \
		src/utils/quote.c \
		src/utils/str_array.c \
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

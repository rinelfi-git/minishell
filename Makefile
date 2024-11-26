NAME = minishell
CC = cc
CARG = -Werror -Wextra -Wall
SRCs = src/main.c \
		src/core/minishell_init.c
OBJs = $(SRCs:.c=.o)
INCs = -Iinclude \
		-Ilibs/libft
LIBs = -Llibs/libft -lft
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

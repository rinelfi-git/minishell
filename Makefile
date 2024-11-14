NAME = minishell
CC = cc
CARG = -Werror -Wextra -Wall
SRCs = src/main.c
OBJs = $(SRCs:.c=.o)
INCs = include

$(NAME) : $(OBJs)
	$(CC) $(CARG) $(INCs) $(OBJs) -o $@

all : $(NAME)

clean :
	rm -rf $(OBJs)

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c
	$(CC) $(CARG) $(INCs) -c $< -o $@

SRC_DIR = src
SRC = src/parser.c src/utils.c src/philosophers.c src/actions.c src/handlers.c src/main.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes -pthread

NAME = philo

all : $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c includes/philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -fr $(OBJ)

fclean : clean
	rm -fr $(NAME)

re : fclean all

.PHONY : all clean fclean re

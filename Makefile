CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iphilosophers -I/inc
LDFLAGS = -L. -lpthread
NAME = philo
SRC_DIR = ./src
INC_DIR = ./inc
INC = $(INC_DIR)/philosophers.h
SRCS = $(SRC_DIR)/philosophers.c $(SRC_DIR)/philosophers_utils.c \
        $(SRC_DIR)/forks.c  $(SRC_DIR)/ft_atoi.c \
        $(SRC_DIR)/time_utils.c $(SRC_DIR)/routine.c \
        $(SRC_DIR)/routine_utils.c $(SRC_DIR)/status_utils.c \
        $(SRC_DIR)/better_sleep.c \
        $(SRC_DIR)/forks_free_utils.c $(SRC_DIR)/main.c $(SRC_DIR)/error_handler.c
        OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	-rm -f $(OBJS)

fclean: clean
	-rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

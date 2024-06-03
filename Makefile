CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iphilosophers -Ift_printf -I.
LDFLAGS = -L. -lpthread -lftprintf
FTPRINTF = libftprintf.a
NAME = philo
SRC_DIR = ./src
INC_DIR = ./inc
INC = $(INC_DIR)/philosophers.h
SRCS = $(SRC_DIR)/philosophers.c $(SRC_DIR)/philosophers_utils.c \
        $(SRC_DIR)/forks.c $(SRC_DIR)/callback.c $(SRC_DIR)/ft_atoi.c \
        $(SRC_DIR)/ft_split.c $(SRC_DIR)/string_utils.c $(SRC_DIR)/time_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FTPRINTF):
	cd ft_printf && $(MAKE)
	@if [ -f ft_printf/$(FTPRINTF) ]; then cp ft_printf/$(FTPRINTF) .; fi

clean:
	-rm -f $(OBJS)
	$(MAKE) -C ft_printf clean

fclean: clean
	-rm -f $(NAME)
	-rm -f $(FTPRINTF)

re: fclean all

.PHONY: all clean fclean re

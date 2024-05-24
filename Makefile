CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Ilibft -Iphilosophers -Ift_printf -I.
LDFLAGS = -L. -lft -lpthread -lftprintf
LIBFT = libft.a
FTPRINTF = libftprintf.a
NAME = philo
SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	cd libft && $(MAKE)
	@if [ -f libft/$(LIBFT) ]; then cp libft/$(LIBFT) .; fi

$(FTPRINTF):
	cd ft_printf && $(MAKE)
	@if [ -f ft_printf/$(FTPRINTF) ]; then cp ft_printf/$(FTPRINTF) .; fi

clean:
	-rm -f $(OBJS)
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean

fclean: clean
	-rm -f $(NAME)
	-rm -f $(LIBFT)
	-rm -f $(FTPRINTF)

re: fclean all

.PHONY: all clean fclean re

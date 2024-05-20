CC = cc -g
INCLUDES = -Ilibft -Iphilosophers -I.
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L. -lft -lpthread
LIBFT = libft.a
NAME = philo
SRCS = main.c 
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(INCLUDES) $(OBJS) $(LDFLAGS ) -o $(NAME)

$(OBJS): $(SRCS)
	$(CC) -c $(SRCS)

$(LIBFT):
	cd libft/ && make
	@if [ -f libft/libft.a ]; then cp libft/libft.a .; fi

clean:
	-rm -f $(OBJS)
	-cd libft/ && make clean

fclean: clean
	-rm -f $(NAME)
	-rm -f $(LIBFT)

re: 
	make fclean
	make all

.PHONY:
	all clean fclean re



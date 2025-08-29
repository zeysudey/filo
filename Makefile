NAME = philo
CFLAGS = -Wall -Wextra -Werror -g -pthread

SRCS = main.c utils.c check_args.c init.c actions.c monitor.c threads.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

main:
	make re
	make clean
	clear

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re
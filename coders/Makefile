CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

NAME = codexion

SRC = main.c parser.c helpers.c simulation.c coder.c dongle.c \
      scheduler.c fifo.c edf.c monitor.c log.c initialize.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

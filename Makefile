NAME = libgnl.a

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
debug: CFLAGS += -g
debug: re
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean: 
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
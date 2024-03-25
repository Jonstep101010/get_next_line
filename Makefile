NAME = libgnl.a

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -I../libft

all: $(NAME)
debug: CFLAGS += -g3
debug: re

LIBFT = ../libft/libft.a
LIBFT_DIR = $(dir $(LIBFT))

# # Build the required library
$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(shell rm -f *.o *.d; rm -rf build)
	
fclean: clean
	rm -f *.a

re: fclean all
.PHONY: all clean fclean re
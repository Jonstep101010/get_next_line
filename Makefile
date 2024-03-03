NAME = libgnl.a

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS =
HEADERS = get_next_line.h

all: $(NAME)
debug: CFLAGS += -g3
debug: re

LIBFT = ../libft/libft.a
LIBFT_DIR = $(dir $(LIBFT))

# # Build the required library
$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS)

.c.o: $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files
-include $(OBJS:.o=.d)
$(LIBFT):
	make -C $(LIBFT_DIR)

clean: $(shell rm -f *.o *.d; rm -rf build)
	make -C $(dir $(LIBFT_DIR)) clean
fclean: clean
	rm -f *.a
	make -C $(dir $(LIBFT_DIR)) fclean

re: fclean all
.PHONY: all clean fclean re
NAME	= libftprintf.a

CC	= gcc
CFLAGS  = -Wall -Wextra -Werror
AR	= ar rcs
RM	= rm -f

SRCS	= printf.c \
		printf2.c \
		printf3.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

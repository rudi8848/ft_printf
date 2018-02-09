NAME = res
LIBFT = libft/libft.a
SRCS = ft_printf.c main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc -o $(NAME)  $(OBJS) -L. $(LIBFT)

$(LIBFT):
	make -C libft

$(OBJS): $(SRCS)
	gcc -c $(SRCS) -g3

clean:
	rm -f *.o
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
re:
	fclean all

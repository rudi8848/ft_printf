NAME = res
LIBFT = libft.a
SRCS = ft_printf.c main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc -o $(NAME)  $(OBJS) -L. -lft

$(LIBFT):
	make -C libft
	mv libft/libft.a .

$(OBJS): $(SRCS)
	gcc -c $(SRCS)

clean:
	rm -f *.o
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
re:
	fclean all

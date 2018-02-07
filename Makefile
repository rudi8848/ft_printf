NAME = res
LIBFT = libft.a

all: $(NAME)

$(NAME): ft_printf.o $(LIBFT)
	gcc -o $(NAME)  ft_printf.o -L. -lft

$(LIBFT):
	make -C libft
	mv libft/libft.a .

ft_printf.o: ft_printf.c
	gcc -c ft_printf.c

clean:
	rm -f *.o
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
re:
	fclean all

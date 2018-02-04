NAME = res

all: $(NAME)
	
$(NAME): ft_printf.o libft.a
	gcc -o $(NAME)  ft_printf.o -L. -lft

main.o: ft_printf.c
	gcc -c ft_printf.c

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
re:
	fclean all

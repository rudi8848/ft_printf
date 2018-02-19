<<<<<<< HEAD
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
=======
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/07 10:12:06 by gvynogra          #+#    #+#              #
#    Updated: 2017/12/25 15:12:43 by gvynogra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	   ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
	   ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	   ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
	   ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
	   ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
	   ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c \
	   ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
	   ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
	   ft_strtrim.c ft_tolower.c ft_toupper.c ft_foreach.c ft_swap.c ft_iswhitespace.c \
	   ft_ispunct.c ft_rot_13.c ft_printf.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)
$(NAME): $(SRCS) $(OBJS)
	gcc -Wall -Wextra -Werror -c $(SRCS) -g3
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
>>>>>>> libftprintf

#include "libft.h"
#include <stdio.h>



int		print_hex_low(size_t n)
{
	int		i;

	i = 0;
	int nb = n;
	while (nb > 0)
	{
		nb /= 16;
		i++;
	}
	if (n >= 16)
	{
		print_hex_low(n / 16);
		print_hex_low(n % 16);
	}
	else if (n >= 10 && n <= 15)
		ft_putchar(n - 10 + 'a');
	else
		ft_putchar(n + '0');
	return (i);
}

int		print_pointer_addr(size_t pointer)
{
	ft_putstr("0x");
	print_hex_low(pointer);
	return (1);
}

int		main(void)
{
	char *a = "qwert";

	print_pointer_addr((size_t)&a);
	printf("\n%p\n", &a);
	return 0;
}
#include "libft.h"
#include <stdio.h>

int		print_hex_low(int n)
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

void
print_ptr(void *p)
{
        unsigned char t[sizeof(p)];
        size_t i;

        memcpy(t, &p, sizeof(p));
        for (i = 0; i < sizeof(p); ++i) {
                printf("%02x", t[i]);
        }
}

int		main(void)
{
	int a = 126;
	//printf("%lu\n", sizeof(&a));
	//printf("%d\n", print_addr(&a));
	print_ptr(&a);
	printf("\n %p\n", &a);
	return 0;
}
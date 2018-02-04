#include <stdarg.h>
#include <stdio.h>

int	ft_add(int c, ...)
{
	va_list vp;
	int nb = 0;
	int res = 0;
	va_start(vp, c);
	while (c > 0)
	{
		nb = va_arg(vp, int);
		printf("%d %c ", nb, c == 1 ? '=' : '+');
		res += nb;
	
		c--;
	}
	va_end(vp);
	printf("%d\n", res);
	return 0;
}

int main(void)
{
	int a = 100;
	int b = 200;
	int c = 300;	

	ft_add(3, a, b, c);
	ft_add(5, 11, 12, 13, 14, 15);
	return 0;
}

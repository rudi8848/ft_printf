#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

/*
		ФОРМАТ:
		%[флаги][ширина][.точность][размер]тип
*/

typedef		int(*pf)();


typedef		enum
{
	CONV_s,
	CONV_S,
	CONV_p,
	CONV_d,
	CONV_D,
	CONV_i,
	CONV_o,
	CONV_O,
	CONV_u,
	CONV_U,
	CONV_x,
	CONV_X,
	CONV_c,
	CONV_C,
	CONVERSIONS
}e_conv;

/*
**-----------------------------------BIT MASKS FOR UNICODE-------------------------------------------------
*/

typedef		enum
{
	ONE_B,
	TWO_B,
	THREE_B,
	FOUR_B,
	BIT_MASKS
}e_bit_masks;

size_t	unicode_masks[BIT_MASKS] = {
	0,									//"0xxx xxxx",
	0xC080,			//49280,			//"110x xxxx    10xx xxxx",
	0xE08080,		//14712960,			//"1110 xxxx    10xx xxxx    10xx xxxx",
	0xF0808080		//4034953344		//"1111 0xxx    10xx xxxx    10xx xxxx    10xx xxxx"
};

int		write_two_bytes(size_t symb);

pf 	p_putchar_unicode[BIT_MASKS];
//p_putchar_unicode[ONE_B] = &write;
p_putchar_unicode[TWO_B] = &write_two_bytes;
//p_putchar_unicode[THREE_B] = &write_three_bytes;
//p_putchar_unicode[FOUR_B] = &write_four_bytes;

//узнаем количество бит в символе
int size_bin(unsigned int symb)
{
  int res = 0;
  while (symb > 0)
  {
    symb /=2;
    res++;
    }
    return res;
  }

int		write_two_bytes(size_t symb)
{
	int res;
	unsigned char o2;
	unsigned char o1;
	unsigned char octet;

	res = 0;
	o2 = (symb << 26) >> 26; // Восстановление первых 6 бит 110xxxxx 10(xxxxxx)
	o1 = ((symb >> 6) << 27) >> 27; // Восстановление последних 5 бит 110(xxxxx) 10xxxxxx
	octet = (unicode_masks[TWO_B] >> 8) | o1; // Применение первой битовой маски ко первому байту
	write(1, &octet, 1);
	res++;
	octet = ((unicode_masks[TWO_B] << 24) >> 24) | o2; // Применение второй битовой маски ко второму байту
	write(1, &octet, 1);
	res++;
	return (res);
}
/*
**----------------------------------------------------------------------------------------------------------
*/

typedef		enum
{
	SF_hh,
	SF_h,
	SF_l,
	SF_ll,
	SF_j,
	SF_z,
	SIZE_FLAGS
}e_size_flags;

/*
**------------------------------------- NUMBER CONVERSIONS ------------------------------------------------
*/

int		print_oct(int n)
{
	int		i;

	i = 0;
	int nb = n;
	while (nb > 0)
	{
		nb /= 8;
		i++;
	}
	if (n >= 8)
	{
		print_oct(n / 8);
		print_oct(n % 8);
	}
	else
		ft_putchar(n + '0');
	return (i);
}

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

int		print_hex_upper(int n)
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
		print_hex_upper(n / 16);
		print_hex_upper(n % 16);
	}
	else if (n >= 10 && n <= 15)
		ft_putchar(n - 10 + 'A');
	else
		ft_putchar(n + '0');
	return (i);
}


/*
**----------------------------------------------------------------------------------------------------------
*/

int		ft_printf(const char *format, ...)
{
	va_list		args;
	va_start(args, format);



	return (0);
}


int main(void)
{

	int x = 125;
	int i;

	//char	*str = "qwerty";
	//wchar_t	*wstr = "фыва";
	wchar_t a = L'а';

	write_two_bytes(a);
	printf("%C\n", a);
	printf("cur max: %d\n", MB_CUR_MAX);

	pf p_convert_functions[CONVERSIONS];

	p_convert_functions[CONV_x] = &print_hex_low;
	p_convert_functions[CONV_X] = &print_hex_upper;
	p_convert_functions[CONV_o] = &print_oct;

	i = p_convert_functions[CONV_x](x);
	ft_putchar('\n');
	printf("%i\n", i);

	i = p_convert_functions[CONV_X](x);
	ft_putchar('\n');
	printf("%i\n", i);

	i = p_convert_functions[CONV_o](x);
	ft_putchar('\n');

	printf("%i\n", i);
	printf("%zu\n", unicode_masks[TWO_B]);

	/*char *ptr = "Hello world!";
	char *np = 0;
	int i = 5;
	unsigned int bs = sizeof(int)*8;
	int mi;
	char buf[80];

	mi = (1 << (bs-1)) + 1;
	ft_printf("my: %s\n", ptr);
	printf("original: %s\n", ptr);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: ft_printf test\n");
	printf("original: ft_printf test\n");
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: %s is null pointer\n", np);
	printf("original: %s is null pointer\n", np);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: %d = 5\n", i);
	printf("original: %d = 5\n", i);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: %d = - max int\n", mi);
	printf("original: %d = - max int\n", mi);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: char %c = 'a'\n", 'a');
	printf("original: char %c = 'a'\n", 'a');
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: hex %x = ff\n", 0xff);
	printf("original: hex %x = ff\n", 0xff);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: hex %02x = 00\n", 0);
	printf("original: hex %02x = 00\n", 0);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf("original: signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: %d %s(s)%", 0, "message");
	printf("original: %d %s(s)%", 0, "message");
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: \n");
	printf("original: \n");
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: %d %s(s) with %%\n", 0, "message");
	printf("original: %d %s(s) with %%\n", 0, "message");
	*/
	return 0;
}
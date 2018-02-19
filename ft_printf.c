<<<<<<< HEAD
#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>
=======
#include "includes/ft_printf.h"
>>>>>>> libftprintf

/*
		ФОРМАТ:
		%[флаги][ширина][.точность][размер]тип

		 то есть при разборе строки после знака %
		 проверяем сначала на флаги,
		 ширина
		 точность
		 размер
		 тип 
*/


/*
	Для обработки численных значений можно использовать UNION. в нем может храниться только одно значение, но типов сколько угодно.
	то есть тайпдефим юнион со всеми возможными типами, а в принтф_путнамбер по флажкам и типу приваеваем юниону значение ва_арг, а затем 
	идем в ф-цию конвертации и печатаем
*/
<<<<<<< HEAD
#define ERROR -1

typedef union u_number
{
	int i;							//<no>
	unsigned u;						//<no>
	size_t st;						//z
	long int l; 						//ld = D
	unsigned long int ul;			//l  O = lo, U = lu
	long long int ll;				//ll
	unsigned long long int ull;	//ll
	short sh;			//h
	unsigned short ush;	//h
	intmax_t ix; 			//j
	uintmax_t uix;			//j
	char ch;				//hh
	unsigned char uch;		//hh
} t_number;


/*
			Modifier      |    d, i      |     o, u, x, X       |     n
         ---------------------------------------------------------------------
         hh                signed char    unsigned char         signed char *
         h                 short          unsigned short        short *
         l (ell)           long           unsigned long         long *
         ll (ell ell)      long long      unsigned long long    long long *
         j                 intmax_t       uintmax_t             intmax_t *		<stdint.h>
         z                 (see note)     size_t                (see note)		<stddef.h> 


*/

typedef		struct s_options
{
	/***----flags----*/
	int				left_align;			//-
	int				show_sign;			//+
	int				space_before;		//' '
	int				show_prefix;		//#
	int				fill_by_zero;		//0

	/***----width-----*/
	int			width;

	/***----precision-----*/
	int			precision;			//.
	/***-----length modificators------*/
	int 			len_hh;
	int 			len_h;
	int 			len_l;
	int 			len_ll;
	int 			len_j;
	int 			len_z;
}					t_options;


typedef		size_t(*t_pf)(char **, va_list*, t_options*);


typedef				enum
{
					CONV_s = 's',
					CONV_S = 'S',
					CONV_p = 'p',
					CONV_d = 'd',
					CONV_D = 'D',
					CONV_i = 'i',
					CONV_o = 'o',
					CONV_O = 'O',
					CONV_u = 'u',
					CONV_U = 'U',
					CONV_x = 'x',
					CONV_X = 'X',
					CONV_c = 'c',
					CONV_C = 'C',
					CONVERSIONS = 127
}					e_conv;

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
=======
//int		write_two_bytes(size_t symb);
>>>>>>> libftprintf

size_t	unicode_masks[BIT_MASKS] = {
	0,									//"0xxx xxxx",
	0xC080,			//49280,			//"110x xxxx    10xx xxxx",
	0xE08080,		//14712960,			//"1110 xxxx    10xx xxxx    10xx xxxx",
	0xF0808080		//4034953344		//"1111 0xxx    10xx xxxx    10xx xxxx    10xx xxxx"
};

<<<<<<< HEAD
int		write_two_bytes(size_t symb);

t_pf 	p_putchar_unicode[BIT_MASKS];

=======


t_pf 	p_putchar_unicode[BIT_MASKS];
int	fillnchar(int len, int width, char c);
>>>>>>> libftprintf


//узнаем количество бит в символе
int size_bin(size_t symb)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
  int res = 0;
  while (symb > 0)
  {
    symb /=2;
    res++;
    }
    return res;
  }

<<<<<<< HEAD


size_t		ft_printf_putstr(char **fmt, va_list *args, t_options *options)
{
	char *str = (char*)va_arg(*args, const char*);
	ft_putstr(str);
	return (ft_strlen(str));
}


=======
int		ft_print_null_string(void)
{
	ft_putstr("(null)");
	return (6);
}

size_t		ft_printf_putstr(char **fmt, va_list *args, t_options *options, int *res)
{
	int len;
	int ret = 0;

	len = 0;
	if (!fmt || !options)		//<-------- to do
		exit(ERROR);
	char *str = (char*)va_arg(*args, const char*);
	char *tmp = NULL;
	if (str)
	{
			len = ft_strlen(str);
			if (options->is_set_precision && options->precision < len)
			{
				tmp = (char*)ft_memalloc((options->precision + 1)*sizeof(char));
				tmp = ft_strncpy(tmp, str, options->precision);
				len = options->precision;
			}
			if (len < options->width && !options->left_align)
			{
				if (options->fill_by_zero)
					ret += fillnchar(len, options->width, '0');
				else
					ret += fillnchar(len, options->width, ' ');
				tmp ? ft_putstr(tmp) : ft_putstr(str);
				ret += len;
			}
			else if (len < options->width && options->left_align)
			{
				tmp ? ft_putstr(tmp) : ft_putstr(str);
				ret += len;
				ret += fillnchar(ret, options->width, ' ');
			}
			else
			{
				tmp ? ft_putstr(tmp) : ft_putstr(str);
				ret += len;
			}
			*res += ret;
			if (tmp)
				free(tmp);
		}
	else
			*res += ft_print_null_string();
	return (len);
}

/*
>>>>>>> libftprintf

int		write_two_bytes(size_t symb)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int 			res;
	unsigned char 	o2;
	unsigned char 	o1;
	unsigned char 	octet;

	res = 0;
	o2 = (symb << 26) >> 26;
	o1 = ((symb >> 6) << 27) >> 27;
	octet = (unicode_masks[TWO_B] >> 8) | o1;
	write(1, &octet, 1);
	res++;
	octet = ((unicode_masks[TWO_B] << 24) >> 24) | o2;
	write(1, &octet, 1);
	res++;
	return (res);
}

int		write_three_bytes(size_t symb)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int 			res;
	unsigned char 	o3;
	unsigned char 	o2;
	unsigned char 	o1;
	unsigned char 	octet;

	res = 0;
	o3 = (symb << 26) >> 26;
	o2 = ((symb >> 6) << 26) >> 26;
	o1 = ((symb >> 12) << 28) >> 28;
	octet = (unicode_masks[THREE_B] >> 16) | o1;
	write(1, &octet, 1);
	res++;
	octet = ((unicode_masks[THREE_B] << 16) >> 24) | o2;
	write(1, &octet, 1);
	octet = ((unicode_masks[THREE_B] << 24) >> 24) | o3;
	write(1, &octet, 1);
	res++;
	return (res);
}

int		write_four_bytes(size_t symb)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int 			res;
	unsigned char 	o4;
	unsigned char 	o3;
	unsigned char	o2;
	unsigned char 	o1;
	unsigned char 	octet;

	res = 0;
	o4 = (symb << 26) >> 26;
	o3 = ((symb >> 6) << 26) >> 26;
	o2 = ((symb >> 12) << 26) >> 26;
	o1 = ((symb >> 18) << 29) >> 29;

	octet = (unicode_masks[FOUR_B] >> 24) | o1;
	write(1, &octet, 1);
	res++;
	octet = ((unicode_masks[FOUR_B] << 8) >> 24) | o2;
	write(1, &octet, 1);
	res++;
	octet = ((unicode_masks[FOUR_B] << 16) >> 24) | o3;
	write(1, &octet, 1);
	res++;
	octet = ((unicode_masks[FOUR_B] << 24) >> 24) | o4;
	write(1, &octet, 1);
	res++;
	return (res);
}
<<<<<<< HEAD

size_t		ft_printf_putchar(char **fmt, va_list *args, t_options *options)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int symb;
	int len;

	symb = va_arg(*args, int);
	len = size_bin(symb);

	if (len < 8)
		ft_putchar(symb);
	else if (len < 16)
		write_two_bytes(symb);
	else if (symb < 32)
		write_three_bytes(symb);
	else
		write_four_bytes(symb);
=======
*/

void    ft_putwchar(wchar_t chr)
{
    if (chr <= 0x7F)
        ft_putchar(chr);
    else if (chr <= 0x7FF)
    {
        ft_putchar((chr >> 6) + 0xC0);
        ft_putchar((chr & 0x3F) + 0x80);
    }
    else if (chr <= 0xFFFF)
    {
        ft_putchar((chr >> 12) + 0xE0);
        ft_putchar(((chr >> 6) & 0x3F) + 0x80);
        ft_putchar((chr & 0x3F) + 0x80);
    }
    else if (chr <= 0x10FFFF)
    {
        ft_putchar((chr >> 18) + 0xF0);
        ft_putchar(((chr >> 12) & 0x3F) + 0x80);
        ft_putchar(((chr >> 6) & 0x3F) + 0x80);
        ft_putchar((chr & 0x3F) + 0x80);
    }
}

size_t		ft_printf_putchar(char **fmt, va_list *args, t_options *options, int *res)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int symb;
	char *ptr;

	if (options->width && !options->left_align)
		*res += fillnchar(1, options->width, ' ');
	ptr = *fmt;
	if (args)
	{
		symb = va_arg(*args, int);
		if (*ptr == 'c')
			ft_putchar(symb);
		else
			ft_putwchar(symb);
	}
	else
		ft_putchar(*ptr);
	if (options->width && options->left_align)
		*res += fillnchar(1, options->width, ' ');
	*res += 1;
>>>>>>> libftprintf
	return (1);
}
//int		print_wstr(int *wstr);


/*
**----------------------------------------------------------------------------------------------------------
*/



/*
**------------------------------------- NUMBER CONVERSIONS ------------------------------------------------
*/

<<<<<<< HEAD
/*
//----------------------itoa_base------------------------
int		ft_nbr_len(int value, int base)
{
	int			len;
	unsigned	nbr;

	len = 0;
	if (value == 0)
		return (1);
	else if (value < 0)
	{
		if (base == 10)
			len++;
		nbr = -value;
	}
	else
		nbr = value;
=======
int	ft_nbr_length(t_number n,int  base, t_options *options)
{
	int len;
	unsigned nbr;

	len = 0;
	nbr = 0;
	if (n.i < 0)
	{
		if (base == 10)
			len++;
		nbr = -n.i;
	}
	else if (n.i == 0)
		len++;
	else
		nbr = n.i;
>>>>>>> libftprintf
	while (nbr)
	{
		nbr /= base;
		len++;
	}
<<<<<<< HEAD
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	int				len;
	unsigned int	res;
	char			*nbr;

	len = ft_nbr_len(value, base);
	if (value < 0)
		res = -value;
	else
		res = value;
	if (!(nbr = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	nbr[len] = '\0';
	while (len-- > 0)
	{
		nbr[len] = (res % base) + (res % base > 9 ? 'A' - 10 : '0');		//<<<--- '?' forbidden by Norm
		res /= base;
	}
	if (value < 0 && base == 10)
		nbr[0] = '-';
	return (nbr);
}
//-----------------------------------------------------------
*/


int		print_oct(size_t n)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int		i;

	i = 0;
	size_t nb = n;
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
=======
	//if (options->show_sign && base == 10 && n.i >= 0)
	//	len++;
	//else if (options->space_before && base == 10 && n.i >= 0)
	//	len++;
	if (options->show_prefix)
	{
		 if (base == 16)
			len += 2;
	}
	return (len);
}


void		print_oct(size_t n)
{
	if (n >= 8)
	{
		print_oct(n >> 3);
		ft_putchar(n % 8 + '0');
	}
	else
		ft_putchar(n + '0');
>>>>>>> libftprintf
}



<<<<<<< HEAD
int		print_hex_low(size_t n)
{
//	printf("--------------------------------------->%s\n", __FUNCTION__);
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

int		print_hex_upper(size_t n)
{
//	printf("--------------------------------------->%s\n", __FUNCTION__);
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

int		print_pointer_addr(size_t ap)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	ft_putstr("0x");
	return (print_hex_low(ap));
}


int		print_dec(ssize_t n)
{
//	printf("--------------------------------------->%s\n", __FUNCTION__);
	size_t nbr;
	int i;
	i = 0;
	if (n < 0)
	{
		if (n <= 0);
		i++;
		nbr = -n;
	}
	else
		nbr = n;
	if (n < 0)
		ft_putchar('-');
	if (nbr >= 10)
	{
		print_dec(nbr / 10);
		print_dec(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
	while (n != 0)
	{
		n /= 10;
		i++;
	}
//	printf("len = %d\n", i);
	return (i);
}

size_t	ft_printf_putnbr(char **fmt, va_list *args, t_options *options)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	ssize_t		nbr;
	int ret;
	char *ptr;

	ptr = (char*)*fmt;
	nbr = va_arg(*args, ssize_t);
	if (*ptr == 'o' || *ptr == 'O')
	{
		if (options->show_prefix)
			ft_putchar('0');
		ret = print_oct(nbr);
	}
	else if (*ptr == 'd' || *ptr == 'i' || *ptr == 'D')
		print_dec(nbr);
	else if (*ptr == 'x')
	{
		if (options->show_prefix)
			ft_putstr("0x");
		ret = print_hex_low(nbr);
	}
	else if (*ptr == 'X')
	{
		if (options->show_prefix)
			ft_putstr("0X");
		ret = print_hex_upper(nbr);
	}
	else if (*ptr == 'p')
		ret = print_pointer_addr((size_t)nbr);
=======
void		print_hex(size_t n, char a)
{
	if (n >= 16)
	{
		print_hex(n >> 4, a);
		print_hex(n % 16, a);
	}
	else if (n >= 10 && n <= 15)
		ft_putchar(n - 10 + a);
	else
		ft_putchar(n + '0');
}


void		print_dec(int n)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	//printf("number: %zd\n", n);
	//остальные типы срабатывают некорректно
	unsigned nbr;
	
	if (n < 0)
	{
		ft_putchar('-');
		nbr = -n;
	}
	else
		nbr = n;	
	if (nbr >= 10)
	{
		print_dec(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
	else
		ft_putchar(nbr + '0');
}

int	fillnchar(int len, int width, char c)
{
	int i = 0;
	while (len < width)
	{
		ft_putchar(c);
		len++;
		i++;
	}
	return (i);
}

size_t	ft_printf_putnbr_oct(char **fmt, va_list *args, t_options *options, int *res)
{
	t_number	nbr;
	int		len;
	int 		ret = 0;
	if (!fmt)
		exit(ERROR);
	nbr.i = va_arg(*args, int);
	if (!nbr.i && options->is_set_precision &&!options->precision && !options->show_prefix)
	{
		ret = fillnchar(0, options->width, ' ');
		*res += ret;
		return (ret);
	}
	len = ft_nbr_length(nbr, 8, options);

	if (nbr.i != 0  && options->show_prefix)
	{
		if (options->precision < len)
			options->precision = len + 1;
	}
	if (options->width > len && !options->left_align)
	{
		if (options->fill_by_zero && !options->precision)
				ret += fillnchar(len, options->width, '0');
		else if (options->precision > len)
			{
				ret += fillnchar(options->precision, options->width, ' ');
				ret += fillnchar(len, options->precision, '0');
			}
		else
				ret += fillnchar(len, options->width, ' ');
			print_oct(nbr.i);
			ret += len;
	}
	
	else if (options->width > len && options->left_align)
	{
			if (options->precision > len)
				ret += fillnchar(len, options->precision, '0');
			print_oct(nbr.i);
			ret += len;
			
		ret += fillnchar(ret, options->width, ' ');
	}
	else
	{
			if (options->precision > len)
				ret += fillnchar(len, options->precision, '0');
			print_oct(nbr.i);
			ret += len;
	}
	*res += ret;
	return (ret);
}

size_t	ft_printf_putnbr_hex(char **fmt, va_list *args, t_options *options, int *res)
{
		t_number	nbr;
	int		len;
	char *ptr;
	int ret = 0;

	ptr = (char*)*fmt;	
	nbr.i = va_arg(*args, int);
	
	if (nbr.i == 0)
		(options->show_prefix = 0);
	if (*ptr == 'p')
		(options->show_prefix = 1);
	if (!nbr.i && options->is_set_precision &&!options->precision)
	{
		if (*ptr == 'p')
			{
				ft_putstr("0x");
				ret += 2;
			}
		ret += fillnchar(0, options->width, ' ');
		*res += ret;
		return (ret);
	}
	len = ft_nbr_length(nbr, 16, options);
	if (options->width > len && !options->left_align)
	{
		if (options->fill_by_zero && !options->precision)
		{
			if (options->show_prefix)
			{
				*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
				ret += fillnchar(len, options->width, '0');
				options->show_prefix = 0;
			}
			else
			ret += fillnchar(len, options->width, '0');
		}
		else if (!(options->precision > len))
			ret += fillnchar(len, options->width, ' ');
		if (options->show_prefix)
			*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
		if (options->precision > len)
			ret += fillnchar(len, options->precision, '0');
		print_hex(nbr.i, *ptr == 'X' ? 'A' : 'a');
		ret += len;
	}
	else if (options->width > len && options->left_align)
	{
		if (options->show_prefix)
			*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
		if (options->precision > len)
			ret += fillnchar(len, options->precision, '0');
		print_hex(nbr.i, *ptr == 'X' ? 'A' : 'a');
		ret += len;
		ret += fillnchar(ret, options->width, ' ');
	}
	else
	{
		if (options->show_prefix)
			*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
		if (options->precision > len)
			ret += fillnchar(len, options->precision, '0');
		print_hex(nbr.i, *ptr == 'X' ? 'A' : 'a');
		ret += len;
	}
	*res += ret;
	return (ret);
}

size_t	ft_printf_putnbr_dec(char **fmt, va_list *args, t_options *options, int *res)
{
	t_number	nbr;
	int		len;
	int ret = 0;

	if (!fmt)
		exit(ERROR);
	nbr.i = va_arg(*args, int);
	if (!nbr.i && options->is_set_precision &&!options->precision)
	{
		ret = fillnchar(0, options->width, ' ');
		*res += ret;
		return (ret);
	}
	len = ft_nbr_length(nbr, 10, options);

	
	if (options->width > len && !options->left_align)
	{
		if (options->fill_by_zero && !options->precision)
		{
			if (nbr.i < 0)
			{
				ft_putchar('-');
				ret += fillnchar(len, options->width, '0');
				nbr.i = -nbr.i;
			}
			else
			{
				if (options->space_before)
				{
					ft_putchar(' ');
					ret++;
				}
				else if (options->show_sign && nbr.i >= 0)
				{
					ft_putchar('+');
					ret++;
				}
				ret += fillnchar(len + ret, options->width, '0');
			}
		}
		else
		{
			if (options->precision < len) 
				ret += fillnchar(len, options->width, ' ');
			else if (options->precision > len && nbr.i >= 0)
				ret += fillnchar(options->precision + options->show_sign, options->width, ' ');
			else if (options->precision > len && nbr.i < 0)
				ret += fillnchar(options->precision + 1, options->width, ' ');
			if (options->show_sign && !options->fill_by_zero && nbr.i >= 0)
			{
				ft_putchar('+');
				ret++;
			}	
			if (options->precision >= len)
			{
				if (nbr.i < 0)
				{
					ft_putchar('-');
					nbr.i = -nbr.i;
					ret++;
					len--;
				}
				ret += fillnchar(len, options->precision, '0');
			}
		}
			print_dec(nbr.i);
			ret += len;
	}





	else if (options->width > len && options->left_align)
	{
		if (options->space_before && nbr.i > 0)
			{
				ft_putchar(' ');
				ret++;
			}
		else if (options->show_sign && nbr.i >= 0)
			{
				ft_putchar('+');
				ret++;
			}
		if (options->precision > len)
		{
			if (nbr.i < 0)
			{
				ft_putchar('-');
				nbr.i = -nbr.i;
			}
			ret += fillnchar(len, options->precision, '0');
		}
			print_dec(nbr.i);
			ret += len;
		ret += fillnchar(ret, options->width, ' ');
	}




	else
	{
		if(options->space_before && nbr.i > 0)
			{
				ft_putchar(' ');
				ret++;
			}
		else if (options->show_sign && nbr.i >= 0)
			{
				ft_putchar('+');
				ret++;
			}
		if (options->precision > len)
		{
			if (nbr.i < 0)
			{
				ft_putchar('-');
				nbr.i = -nbr.i;
				len--;
				ret++;
			}
			ret += fillnchar(len, options->precision, '0');
		}
			print_dec(nbr.i);
			ret += len;
	}
	*res += ret;
>>>>>>> libftprintf
	return (ret);
}




size_t	ft_wstrlen(wchar_t *wstr)
{
<<<<<<< HEAD
	printf("--------------------------------------->%s\n", __FUNCTION__);
	int size;
	size_t len = 0;


	size = size_bin(wstr[len]);
=======
	//int size;
	size_t len = 0;


	//size = size_bin(wstr[len]);
>>>>>>> libftprintf
	
	while (wstr[len] != L'\0')
		len++;
	return (len);
}

<<<<<<< HEAD
size_t	print_wstr(char **fmt, va_list *args, t_options *options)
=======
size_t	print_wstr(char **fmt, va_list *args, t_options *options, int *res)
>>>>>>> libftprintf
{
	size_t i;
	int size;

<<<<<<< HEAD
=======
	if (!fmt || !options)
		exit(ERROR);
>>>>>>> libftprintf
	wchar_t *wstr;
	wstr = (wchar_t *)va_arg(*args, wchar_t*);
	i = 0;
	while (wstr[i] != L'\0')
	{
	size = size_bin(wstr[i]);
	
	//printf(" = %d\n", size);
	
<<<<<<< HEAD
	if (size <= 7)
		 ft_putchar(wstr[i]);
	else if (size <= 15)
		write_two_bytes(wstr[i]);
	else if (size <= 31)
		write_three_bytes(wstr[i]);
	else
		write_four_bytes(wstr[i]);
=======
	ft_putwchar(wstr[i]);
>>>>>>> libftprintf
	
		//printf("in loop %zu\n", i);
//		print(wstr[i]);
		i++;

		}
<<<<<<< HEAD
=======
		*res += i;
>>>>>>> libftprintf
	return (i);
}

/*
**----------------------------------------------------------------------------------------------------------
*/




int		ft_parse_flags(char *fp, t_options *options)
{
	int i;

	i = 0;
	while (fp[i] == '-' || fp[i] == '+' || fp[i] == ' ' || fp[i] == '#' || fp[i] == '0' )
	{
		if(fp[i] == '+')
			options->show_sign = 1;
		else if (fp[i] == ' ')
			options->space_before = 1;
		else if (fp[i] == '#')
			options->show_prefix = 1;
		else if (fp[i] == '0')
			options->fill_by_zero = 1;
		else if (fp[i] == '-')
		{
				options->left_align = 1;
				options->fill_by_zero = 0;
		}
		i++;
	}
<<<<<<< HEAD
=======
	if (options->show_sign && options->space_before)
		options->space_before = 0;
>>>>>>> libftprintf
	return (i);
}

int		ft_parse_width(char *fp, va_list *args, t_options *options)
{
	int i;
	int arg;

	i = 0;
<<<<<<< HEAD
=======
	while (ft_isdigit(fp[i]) || fp[i] == '*')
	{
>>>>>>> libftprintf
	if (ft_isdigit(fp[i]))
		{
			options->width = ft_atoi(fp + i);
			while (ft_isdigit(fp[i]))
				i++;
		}
<<<<<<< HEAD
	else if (*fp == '*')
=======
	if (fp[i] == '*')
>>>>>>> libftprintf
	{
		arg = va_arg(*args, int);
		if (arg < 0)
		{
			arg = -arg;
			options->left_align = 1;
		}
		options->width = arg;
		i++;
	}
<<<<<<< HEAD
=======
	}
>>>>>>> libftprintf
	return (i);
}

int		ft_parse_precision(char *fp, va_list *args, t_options *options)
{
	int i;
	int arg;

	i = 0;
	if (fp[i] == '.')
		{
			i++;
<<<<<<< HEAD
=======
			options->is_set_precision = 1;
>>>>>>> libftprintf
			if (ft_isdigit(fp[i]))
			{
				options->precision = ft_atoi(fp + i);
				while (ft_isdigit(fp[i]))
					i++;
			}
<<<<<<< HEAD
			else if (*fp == '*')
=======
			if (fp[i] == '*')
>>>>>>> libftprintf
			{
				arg = va_arg(*args, int);
				if (arg >= 0)
					options->precision = arg;
<<<<<<< HEAD
			}
			else
				options->precision = 0;
=======
				else
					options->is_set_precision = 0;
				i++;
			}
>>>>>>> libftprintf
		}
	return (i);
}

int		ft_parse_length(char *fp, t_options *options)
{
	int i;

	i = 0;
	if (fp[i] == 'h')
	{
		i++;
		if (fp[i] == 'h')
		{
			options->len_hh = 1;
			i++;
		}
		options->len_h = 1;
	}
	if (fp[i] == 'l')
	{
		i++;
		if (fp[i] == 'l')
		{
			options->len_ll = 1;
			i++;
		}
		options->len_l = 1;
	}
	if (fp[i] == 'j')
	{
		options->len_j = 1;
		i++;
	}
	if (fp[i] == 'z')
	{
		options->len_z = 1;
		i++;
	}
	return (i);
}

t_pf	ft_choose_type(e_conv conv)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	t_pf convert_functions[CONVERSIONS];

	convert_functions[CONV_c] = &ft_printf_putchar;
	convert_functions[CONV_s] = &ft_printf_putstr;
<<<<<<< HEAD
	convert_functions[CONV_d] = &ft_printf_putnbr;
	convert_functions[CONV_D] = &ft_printf_putnbr;
	convert_functions[CONV_i] = &ft_printf_putnbr;
	convert_functions[CONV_o] = &ft_printf_putnbr;
	convert_functions[CONV_O] = &ft_printf_putnbr;
	convert_functions[CONV_x] = &ft_printf_putnbr;
	convert_functions[CONV_X] = &ft_printf_putnbr;
	convert_functions[CONV_p] = &ft_printf_putnbr;
=======
	convert_functions[CONV_d] = &ft_printf_putnbr_dec;
	convert_functions[CONV_D] = &ft_printf_putnbr_dec;
	convert_functions[CONV_i] = &ft_printf_putnbr_dec;
	convert_functions[CONV_u] = &ft_printf_putnbr_dec;
	convert_functions[CONV_U] = &ft_printf_putnbr_dec;
	convert_functions[CONV_o] = &ft_printf_putnbr_oct;
	convert_functions[CONV_O] = &ft_printf_putnbr_oct;
	convert_functions[CONV_x] = &ft_printf_putnbr_hex;
	convert_functions[CONV_X] = &ft_printf_putnbr_hex;
	convert_functions[CONV_p] = &ft_printf_putnbr_hex;
	//convert_functions[CONV_b] = &ft_printf_putnbr_bin;
	//convert_functions[CONV_f] = &ft_prinft_putnbr_float;
	//convert_functions[CONV_F] = &ft_prinft_putnbr_float;
>>>>>>> libftprintf
	convert_functions[CONV_C] = &ft_printf_putchar;
	convert_functions[CONV_S] = &print_wstr;
	return (convert_functions[conv]);
}

<<<<<<< HEAD
=======

>>>>>>> libftprintf
static int check_type(char c)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	if (c == 's' || c == 'S' || c == 'c' || c == 'C')
		return (1);
	else if (c == 'p' || c == 'd' || c == 'D' || c == 'i')
		return (1);
	else if (c == 'o' || c == 'O' || c == 'u' || c == 'U')
		return (1);
	else if (c == 'x' || c == 'X')
		return (1);
	else
		return (0);
}

<<<<<<< HEAD
size_t	ft_parse_options(const char **format, va_list *args/*, int *res*/)
=======

size_t	ft_parse_options(const char **format, va_list *args, int *res)
>>>>>>> libftprintf
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	t_options *options;
	char *fmtp;
	t_pf ft_transformer;
<<<<<<< HEAD
=======

>>>>>>> libftprintf
	options = (t_options*)ft_memalloc(sizeof(t_options));
	if (!options)
		exit(ERROR);
	fmtp = (char*)++(*format);
	fmtp += ft_parse_flags(fmtp, options);
<<<<<<< HEAD
	fmtp += ft_parse_width(fmtp, args, options);	
	fmtp += ft_parse_precision(fmtp, args, options);
	fmtp += ft_parse_length(fmtp, options);
	// ?? проверка на спецификатор?? эта не работает,если после % не идет тип - segmentation fault
//	if (check_type(*fmtp))

		ft_transformer = ft_choose_type(*fmtp);
		ft_transformer(&fmtp, args, options);

//	else
//		fmtp++;
	return (fmtp - *format);

=======
	fmtp += ft_parse_width(fmtp, args, options);
	fmtp += ft_parse_precision(fmtp, args, options);
	fmtp += ft_parse_length(fmtp, options);
	if (*fmtp != '\0')
	{
		if (check_type(*fmtp))
		{
			ft_transformer = ft_choose_type(*fmtp);
			ft_transformer(&fmtp, args, options, res);
		}
		else
				ft_printf_putchar(&fmtp, NULL, options, res);
		if (options)
			free(options);
		return (fmtp - *format);
	}
>>>>>>> libftprintf
return 0;
}


int		ft_printf(const char *format, ...)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	va_list		args;
	int			res = 0;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
<<<<<<< HEAD
		{
			if (*(format + 1) == '%')
			{
				ft_putchar(*format++);
				res++;
			}
			else
			format += ft_parse_options(&format, &args/*, &res*/);		
		}
=======
			format += ft_parse_options(&format, &args, &res);
>>>>>>> libftprintf
		else
		{
			ft_putchar(*format);
			res++;
		}
		format++;
	}
	va_end(args);
	return (res);
}

<<<<<<< HEAD
/*
**------------------------------------------MAIN------------------------------------------------------------
*/

int main(void)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	
	setlocale(LC_ALL, "Rus");
	
	ft_printf("no args\n");
	//ft_printf("args %0. qwe 15\n");
	ft_printf("arg %%\n");
	ft_printf("%s\n", "hello");
	ft_printf("[%c][%c]\n", 'Q', '7');
	ft_printf("%c %s\n",'0', "qwerty");
//	ft_printf("% %s\n",'0', "qwerty");
  ft_printf("--------------------------------------------------\n");

	ft_printf("my: oct 	%#o\n", 100);
	printf("original: oct 	%#o\n", 100);
  ft_printf("--------------------------------------------------\n");

	ft_printf("string: %s\n", "adsf");
	//ft_printf("pointer: %p", &x);
  ft_printf("--------------------------------------------------\n");
	ft_printf("my hex: 	%X\n", 1234);
	printf("original hex: 	%X\n", 1234 );


	int x = 125;

	//char	*str = "qwerty";
	//wchar_t	*wstr = "фыва";
	char d = 'b';
	wchar_t a = L'Ы';
	wchar_t b = L'ࢢ';
	//wchar_t c = L'𐄂';
//printf("%lu\n", sizeof(wchar_t));
	printf("cur max: %d\n", MB_CUR_MAX);

	wchar_t *wstr = L"привет, друг!!!";


	int arab = L'ڲ';
	wchar_t *rus = L"дарова!!!";
	char *ptr;
	ptr = "Hello world!";
	int i = 5;
	int *np = &i;
	unsigned int size_in_bits = sizeof(int)*8;
	int max_int;
	char buf[80];

	max_int = ~(1 << (size_in_bits-1));
	int min_int = 1 << (size_in_bits - 1);
  ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		%s\n", ptr);
	printf("original: 	%s\n", ptr);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		ft_printf test\n");
	printf("original: 	ft_printf test\n");
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		%S\n", rus);
	printf("original: 	%ls\n", rus);
	ft_printf("--------------------------------------------------\n");
	
	
	ft_printf("my: 		%p pointer\n", np);
	printf("original: 	%p pointer\n", np);
	ft_printf("--------------------------------------------------\n");
	
	ft_printf("my: 		%d = 5\n", i);
	printf("original: 	%d = 5\n", i);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		%d =  max int\n", max_int);
	printf("original: 	%d =  max int\n", max_int);
	ft_printf("--------------------------------------------------\n");
	ft_printf("my: 		%d =  max int\n", min_int);
	printf("original: 	%d =  max int\n", min_int);
	ft_printf("--------------------------------------------------\n");


	ft_printf("my: char 	%c = 'a'\n", 'a');
	printf("original: char 	%c = 'a'\n", 'a');
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: hex 	%x = ff\n", 0xff);
	printf("original: hex 	%x = ff\n", 0xff);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: hex 	%02x = 00\n", 0);
	printf("original: hex 	%02x = 00\n", 0);
	ft_printf("--------------------------------------------------\n");

	/*
	ft_printf("my: signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf("original: signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	ft_printf("--------------------------------------------------\n");
*/
	/*
  
	ft_printf("my: %d %s(s)%", 0, "message");
	printf("original: %d %s(s)%", 0, "message");
	ft_printf("--------------------------------------------------\n");
*/
	ft_printf("my: \n");
	printf("original: \n");
	ft_printf("--------------------------------------------------\n");
	
	ft_printf("my: %o %s(s) with %%\n", 10, "message");
	printf("original: %o %s(s) with %%\n", 10, "message");

	ft_printf("--------------------------------------------------\n");
	printf("	MB_CUR_MAX: %d\n", MB_CUR_MAX);


	ft_printf("--------------------------------------------------\n");

	
	ft_printf("my: %c\n",  arab);
	printf("original:  %c\n",  arab);

	ft_printf("--------------------------------------------------\n");

	printf("%d\n", size_bin(arab));
	ft_printf("my: %C\n", arab);
	printf("original: %lc\n", arab);


	ft_printf("--------------------------------------------------\n");
	ft_printf("wstr:	%S\n",rus);	
	return 0;
}

=======
>>>>>>> libftprintf

#include "includes/ft_printf.h"

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
//int		write_two_bytes(size_t symb);

size_t	unicode_masks[BIT_MASKS] = {
	0,									//"0xxx xxxx",
	0xC080,			//49280,			//"110x xxxx    10xx xxxx",
	0xE08080,		//14712960,			//"1110 xxxx    10xx xxxx    10xx xxxx",
	0xF0808080		//4034953344		//"1111 0xxx    10xx xxxx    10xx xxxx    10xx xxxx"
};



t_pf 	p_putchar_unicode[BIT_MASKS];
int	fillnchar(int len, int width, char c);


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

size_t		ft_printf_putchar(char **fmt, va_list *args, t_options *options, int *res)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	int symb;
	int len;
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
		{
			len = size_bin(symb);
			if (len < 8)
				ft_putchar(symb);
			else if (len < 16)
				write_two_bytes(symb);
			else if (symb < 32)
				write_three_bytes(symb);
			else
				write_four_bytes(symb);
		}
	}
	else
		ft_putchar(*ptr);
	if (options->width && options->left_align)
		*res += fillnchar(1, options->width, ' ');
	*res += 1;
	return (1);
}
//int		print_wstr(int *wstr);


/*
**----------------------------------------------------------------------------------------------------------
*/



/*
**------------------------------------- NUMBER CONVERSIONS ------------------------------------------------
*/

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
	while (nbr)
	{
		nbr /= base;
		len++;
	}
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
}



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
		else
		{
			if (options->precision)
				ret += fillnchar(options->precision, options->width, ' ');
			if (options->precision > len)
				ret += fillnchar(len, options->precision, '0');
			else
				ret += fillnchar(len, options->width, ' ');
		}
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
		else
			ret += fillnchar(len, options->width, ' ');
		if (options->show_prefix)
			*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
		print_hex(nbr.i, *ptr == 'X' ? 'A' : 'a');
		ret += len;
	}
	else if (options->width > len && options->left_align)
	{
		if (options->show_prefix)
			*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
		print_hex(nbr.i, *ptr == 'X' ? 'A' : 'a');
		ret += len;
		ret += fillnchar(ret, options->width, ' ');
	}
	else
	{
		if (options->show_prefix)
			*ptr == 'X' ? ft_putstr("0X") : ft_putstr("0x");
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
		else if (options->precision > len)
				ret += fillnchar(options->precision + options->show_sign, options->width, ' ');
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
	return (ret);
}




size_t	ft_wstrlen(wchar_t *wstr)
{
	//int size;
	size_t len = 0;


	//size = size_bin(wstr[len]);
	
	while (wstr[len] != L'\0')
		len++;
	return (len);
}

size_t	print_wstr(char **fmt, va_list *args, t_options *options, int *res)
{
	size_t i;
	int size;

	if (!fmt || !options)
		exit(ERROR);
	wchar_t *wstr;
	wstr = (wchar_t *)va_arg(*args, wchar_t*);
	i = 0;
	while (wstr[i] != L'\0')
	{
	size = size_bin(wstr[i]);
	
	//printf(" = %d\n", size);
	
	if (size < 8)
		 ft_putchar(wstr[i]);
	else if (size < 16)
		write_two_bytes(wstr[i]);
	else if (size < 32)
		write_three_bytes(wstr[i]);
	else
		write_four_bytes(wstr[i]);
	
		//printf("in loop %zu\n", i);
//		print(wstr[i]);
		i++;

		}
		*res += i;
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
	if (options->show_sign && options->space_before)
		options->space_before = 0;
	return (i);
}

int		ft_parse_width(char *fp, va_list *args, t_options *options)
{
	int i;
	int arg;

	i = 0;
	if (ft_isdigit(fp[i]))
		{
			options->width = ft_atoi(fp + i);
			while (ft_isdigit(fp[i]))
				i++;
		}
	else if (*fp == '*')
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
			options->is_set_precision = 1;
			if (ft_isdigit(fp[i]))
			{
				options->precision = ft_atoi(fp + i);
				while (ft_isdigit(fp[i]))
					i++;
			}
			else if (*fp == '*')
			{
				arg = va_arg(*args, int);
				if (arg >= 0)
					options->precision = arg;
			}
		}
	else
				options->is_set_precision = 0;
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
	convert_functions[CONV_C] = &ft_printf_putchar;
	convert_functions[CONV_S] = &print_wstr;
	return (convert_functions[conv]);
}


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


size_t	ft_parse_options(const char **format, va_list *args, int *res)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	t_options *options;
	char *fmtp;
	t_pf ft_transformer;

	options = (t_options*)ft_memalloc(sizeof(t_options));
	if (!options)
		exit(ERROR);
	fmtp = (char*)++(*format);
	fmtp += ft_parse_flags(fmtp, options);
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
			format += ft_parse_options(&format, &args, &res);
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


#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#define ERROR -1

typedef		struct s_options
{
	/***----flags----*/
	int				left_align;			//-
	int				show_sign;			//+
	int				space_before;		//' '
	int				show_prefix;		//#
	int				fill_by_zero;		//0

	/***----width-----*/
	size_t			width;

	/***----precision-----*/
	size_t			precision;			//.
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

size_t		ft_printf_putchar(char **fmt, va_list *args, t_options *options)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	ft_putchar(va_arg(*args, int));
	return (1);
}

size_t		ft_printf_putstr(char **fmt, va_list *args, t_options *options)
{
	char *str = (char*)va_arg(*args, const char*);
	ft_putstr(str);
	return (ft_strlen(str));
}

int		ft_parse_flags(char *fp, t_options *options)
{
	int i;

	i = 0;
	if (fp[i] == '-')
	{
			options->left_align = 1;
			i++;
	}
	else if(fp[i] == '+')
	{
		options->show_sign = 1;
		i++;
	}
	else if (fp[i] == ' ')
	{
		options->space_before = 1;
		i++;
	}
	else if (fp[i] == '#')
	{
		options->show_prefix = 1;
		i++;
	}
	else if (fp[i] == '0')
	{
		options->fill_by_zero = 1;
		i++;
	}
	return (i);
}

int		ft_parse_width(char *fp, t_options *options)
{
	int i;

	i = 0;
	if (ft_isdigit(fp[i]))
		{
			options->width = ft_atoi(fp + i);
			while (ft_isdigit(fp[i]))
				i++;
		}
	return (i);
}

int		ft_parse_percision(char *fp, t_options *options)
{
	int i;

	i = 0;
	if (fp[i] == '.')
		{
			i++;
			options->precision = ft_atoi(fp + i);
			while (ft_isdigit(fp[i]))
				i++;
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

t_pf	ft_choose_specificator(char conv)
{
	t_pf convert_functions[CONVERSIONS];

	convert_functions[CONV_c] = &write_one_byte;
	convert_functions[CONV_s] = &ft_printf_putstr;
	return (convert_functions[conv]);
}


size_t	ft_parse_options(const char **format, va_list *args/*, int *res*/)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	t_options *options;
	char *fmtp;
	t_pf ft_transformer;
	options = (t_options*)ft_memalloc(sizeof(t_options));
	if (!options)
		return ERROR;
	fmtp = (char*)++(*format);
	fmtp += ft_parse_flags(fmtp, options);
	fmtp += ft_parse_width(fmtp, options);	
	fmtp += ft_parse_percision(fmtp, options);
	fmtp += ft_parse_length(fmtp, options);
	ft_transformer = ft_choose_specificator(*fmtp);
	ft_transformer(&fmtp, args, options);
	//fmtp++;
	return (fmtp - *format);
}


int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			res = 0;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) == '%')
			{
				ft_putchar(*format++);
				res++;
			}
			else
			format += ft_parse_options(&format, &args/*, &res*/);		
		}
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

int main(void)
{
	ft_printf("no args\n");
	//ft_printf("args %0. qwe 15\n");
	ft_printf("arg %%\n");
	ft_printf("[%c][%c]\n", 'Q', '7');
	ft_printf("%c %s\n",'0', "qwerty");

	return (0);
}
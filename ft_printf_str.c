#include "includes/ft_printf.h"

int		ft_print_null_string(void)
{
	write(1, "(null)", 6);
	return (6);
}

ssize_t		ft_printf_putchar(char **fmt, va_list *args, t_options *options, int *res)
{
	int symb;
	char *ptr;
	int ret = 0;

	ptr = *fmt;
	if (args)
	{
		symb = va_arg(*args, int);
		if (options->width && !options->left_align)
		{
			if (options->fill_by_zero)
				ret += fillnchar(ft_nb_bytes(ft_nb_bits(symb)), options->width, '0');
			else
				ret += fillnchar(ft_nb_bytes(ft_nb_bits(symb)), options->width, ' ');
		}
		if (*ptr == 'c' && !options->len_l)
		{
			ft_putchar(symb);
			ret += 1;
		}
		else
			ret += ft_putwchar(symb);
	}
	else
	{
		if (options->width && !options->left_align)
		{
			if (options->fill_by_zero)
				ret += fillnchar(1, options->width, '0');
			else
				ret += fillnchar(1, options->width, ' ');
		}
		ft_putchar(*ptr);
		ret += 1;
	}
	if (options->width && options->left_align)
		ret += fillnchar(1, options->width, ' ');
	*res += ret;
	return (ret);
}

ssize_t		ft_printf_putstr(char **fmt, va_list *args, t_options *options, int *res)
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
		(options->width && options->is_set_precision) ? (*res += fillnchar(0, options->width, '0')) : (*res += ft_print_null_string());
	return (len);
}

size_t		ft_wstrlen(wchar_t *wstr)
{
	size_t len = 0;

	while (wstr[len] != L'\0')
		len++;
	return (len);
}

ssize_t	print_wstr(char **fmt, va_list *args, t_options *options, int *res)
{
	int i;
	wchar_t *wstr = NULL;
	int ret = 0;
	int len;

	i = 0;
	if (!fmt || !options)
		exit(ERROR);
	wstr = (wchar_t *)va_arg(*args, wchar_t*);
	if (!wstr)
	{
		ft_print_null_string();
		*res += 6;
		return (6);
	}
	len = ft_wstrlen(wstr);
	if (options->is_set_precision)
	{
		if (options->fill_by_zero)
		{
			if (options->precision)
				ret += fillnchar(0, options->precision, '0');
			else
				ret += fillnchar(0, options->width, '0');
		}
		while (ret < options->precision)
		{
			ret += ft_putwchar(wstr[i]);
			i++;
		}
		return (ret);
	}
	else
	{
		while (wstr[i] != L'\0')
		{
			ret += ft_putwchar(wstr[i]);
			i++;
		}
	}
	*res += ret;
	return (ret);
}
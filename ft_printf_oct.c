#include "includes/ft_printf.h"

ssize_t		ft_printf_putnbr_oct(char **fmt, va_list *args, t_options *options, int *res)
{
	uintmax_t	nbr;
	int			len;
	int 		ret;

	ret = 0;
	if (!fmt)
		exit(ERROR);
	nbr = ft_cut_unsigned(args, options);
	if (!nbr && options->is_set_precision &&!options->precision && !options->show_prefix)
	{
		ret = fillnchar(0, options->width, ' ');
		*res += ret;
		return (ret);
	}
	len = ft_unbr_length(&nbr, 8);

	if (nbr != 0  && options->show_prefix)
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
		print_oct(nbr);
		ret += len;
	}

	else if (options->width > len && options->left_align)
	{
		if (options->precision > len)
			ret += fillnchar(len, options->precision, '0');
		print_oct(nbr);
		ret += len;		
		ret += fillnchar(ret, options->width, ' ');
	}
	else
	{
		if (options->precision > len)
			ret += fillnchar(len, options->precision, '0');
		print_oct(nbr);
		ret += len;
	}
	*res += ret;
	return (ret);
}
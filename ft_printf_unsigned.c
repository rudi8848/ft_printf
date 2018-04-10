#include "includes/ft_printf.h"

ssize_t	ft_printf_putnbr_udec(char **fmt, va_list *args, t_options *options, int *res)
{
	uintmax_t	nbr;
	int		len;
	int ret = 0;

	if (!fmt)
		exit(ERROR);
	nbr = ft_cut_unsigned(args, options);
	len = ft_unbr_length(&nbr, 10);

	if (!nbr && options->is_set_precision &&!options->precision)
	{
		ret = fillnchar(0, options->width, ' ');
		*res += ret;
		return (ret);
	}
	if (options->width > len && !options->left_align)
	{
		if (options->fill_by_zero && !options->precision)
		{
			ret += fillnchar(len + ret, options->width, '0');
		}
		else
		{
			if (options->precision < len) 
				ret += fillnchar(len, options->width, ' ');
			else if (options->precision > len && nbr)
				ret += fillnchar(options->precision + options->show_sign, options->width, ' ');
			
			if (options->precision >= len)
			{
				ret += fillnchar(len, options->precision, '0');
			}
		}
		print_udec(nbr);
		ret += len;
	}

	else if (options->width > len && options->left_align)
	{
		if (options->precision > len)
		{
			ret += fillnchar(len, options->precision, '0');
		}
		print_udec(nbr);
		ret += len;
		ret += fillnchar(ret, options->width, ' ');
	}

	else
	{
		if (options->precision > len)
		{
			ret += fillnchar(len, options->precision, '0');
		}
		print_udec(nbr);
		ret += len;
	}
	*res += ret;
	return (ret);
}

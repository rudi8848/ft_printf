#include "includes/ft_printf.h"

ssize_t	ft_printf_putnbr_sdec(char **fmt, va_list *args, t_options *options, int *res)
{
	intmax_t	nbr;
	int		len;
	int ret = 0;

	if (!fmt)
		exit(ERROR);
	nbr = ft_cut_signed(args, options);
	len = ft_snbr_length(&nbr, 10);
	if (!nbr && options->is_set_precision && !options->precision)
	{
		ret = fillnchar(0, options->width, ' ');
		*res += ret;
		return (ret);
	}
	if (options->width > len && !options->left_align)
	{
		if (options->fill_by_zero && !options->precision)
		{
			if (nbr < 0)
			{
				ft_putchar('-');
				ret += fillnchar(len, options->width, '0');
				nbr = -nbr;
			}
			else
			{
				if (options->space_before)
				{
					ft_putchar(' ');
					ret++;
				}
				else if (options->show_sign && nbr >= 0)
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
			else if (options->precision > len && nbr >= 0)
			{
				if (options->space_before)
					ret += write(1, " ", 1);
				ret += fillnchar(options->precision + options->show_sign + options->space_before, options->width, ' ');
			}
			else if (options->precision > len && nbr < 0)
				ret += fillnchar(options->precision + 1, options->width, ' ');
			else if (options->width > options->precision && options->width > len && nbr >=0)
				ret += fillnchar(options->precision, options->width, ' ');
			if (options->show_sign && !options->fill_by_zero && nbr >= 0)
			{
				ft_putchar('+');
				ret++;
			}	
			if (options->precision >= len)
			{
				if (nbr < 0)
				{
					ft_putchar('-');
					nbr = -nbr;
					ret++;
					len--;
				}
				ret += fillnchar(len, options->precision, '0');
			}
		}
			print_sdec(nbr);
			ret += len;
	}

	else if (options->width > len && options->left_align)
	{
		if (options->space_before && nbr > 0)
		{
			ft_putchar(' ');
			ret++;
		}
		else if (options->show_sign && nbr >= 0)
		{
			ft_putchar('+');
			ret++;
		}
		if (options->precision > len)
		{
			if (nbr < 0)
			{
				ft_putchar('-');
				nbr = -nbr;
			}
			ret += fillnchar(len, options->precision, '0');
		}
		print_sdec(nbr);
		ret += len;
		ret += fillnchar(ret, options->width, ' ');
	}
	else
	{
		if(options->space_before && nbr > 0)
		{
			ft_putchar(' ');
			ret++;
		}
		else if (options->show_sign && nbr >= 0)
		{
			ft_putchar('+');
			ret++;
		}
		if (options->precision > len)
		{
			if (nbr < 0)
			{
				ft_putchar('-');
				nbr = -nbr;
				len--;
				ret++;
			}
			ret += fillnchar(len, options->precision, '0');
		}
		print_sdec(nbr);
		ret += len;
	}
	*res += ret;
	return (ret);
}

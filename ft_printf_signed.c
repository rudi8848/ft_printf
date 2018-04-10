/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_signed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:08:48 by gvynogra          #+#    #+#             */
/*   Updated: 2018/04/10 18:08:55 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_s_no_precision(int width, int *res)
{
	int ret;

	ret = 0;
	ret = fillnchar(0, width, ' ');
	*res += ret;
	return (ret);
}

ssize_t	ft_printf_putnbr_sdec(char **fmt, va_list *args, t_propt *opt, int *res)
{
	intmax_t	nbr;
	int		len;
	int ret = 0;

	if (!fmt)
		exit(ERROR);
	nbr = ft_cut_signed(args, opt);
	len = ft_snbr_length(&nbr, 10);
	if (!nbr && opt->is_set_precision && !opt->precision)
		return (ft_s_no_precision(opt->width, res));
	if (opt->width > len && !opt->left_align)
	{
		if (opt->fill_by_zero && !opt->precision)
		{
			if (nbr < 0)
			{
				ft_putchar('-');
				ret += fillnchar(len, opt->width, '0');
				nbr = -nbr;
			}
			else
			{
				if (opt->space_before)
				{
					ft_putchar(' ');
					ret++;
				}
				else if (opt->show_sign && nbr >= 0)
				{
					ft_putchar('+');
					ret++;
				}
				ret += fillnchar(len + ret, opt->width, '0');
			}
		}
		else
		{
			if (opt->precision < len) 
				ret += fillnchar(len, opt->width, ' ');
			else if (opt->precision > len && nbr >= 0)
			{
				if (opt->space_before)
					ret += write(1, " ", 1);
				ret += fillnchar(opt->precision + opt->show_sign + opt->space_before, opt->width, ' ');
			}
			else if (opt->precision > len && nbr < 0)
				ret += fillnchar(opt->precision + 1, opt->width, ' ');
			else if (opt->width > opt->precision && opt->width > len && nbr >= 0)
				ret += fillnchar(opt->precision, opt->width, ' ');
			if (opt->show_sign && !opt->fill_by_zero && nbr >= 0)
			{
				ft_putchar('+');
				ret++;
			}	
			if (opt->precision >= len)
			{
				if (nbr < 0)
				{
					ft_putchar('-');
					nbr = -nbr;
					ret++;
					len--;
				}
				ret += fillnchar(len, opt->precision, '0');
			}
		}
			print_sdec(nbr);
			ret += len;
	}

	else if (opt->width > len && opt->left_align)
	{
		if (opt->space_before && nbr > 0)
		{
			ft_putchar(' ');
			ret++;
		}
		else if (opt->show_sign && nbr >= 0)
		{
			ft_putchar('+');
			ret++;
		}
		if (opt->precision > len)
		{
			if (nbr < 0)
			{
				ft_putchar('-');
				nbr = -nbr;
			}
			ret += fillnchar(len, opt->precision, '0');
		}
		print_sdec(nbr);
		ret += len;
		ret += fillnchar(ret, opt->width, ' ');
	}
	else
	{
		if (opt->space_before && nbr > 0)
		{
			ft_putchar(' ');
			ret++;
		}
		else if (opt->show_sign && nbr >= 0)
		{
			ft_putchar('+');
			ret++;
		}
		if (opt->precision > len)
		{
			if (nbr < 0)
			{
				ft_putchar('-');
				nbr = -nbr;
				len--;
				ret++;
			}
			ret += fillnchar(len, opt->precision, '0');
		}
		print_sdec(nbr);
		ret += len;
	}
	*res += ret;
	return (ret);
}

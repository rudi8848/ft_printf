/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:18:37 by gvynogra          #+#    #+#             */
/*   Updated: 2018/04/10 16:21:42 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

ssize_t	ft_printf_putnbr_hex(char **fmt, va_list *args, t_options *opt, int *res)
{
	uintmax_t	nbr;
	int			len;
	char		*ptr;
	int			ret;

	ptr = (char*)*fmt;
	nbr = ft_cut_unsigned(args, opt);
	ret = 0;
	if (nbr == 0)
		(opt->show_prefix = 0);
	if (*ptr == 'p')
		(opt->show_prefix = 1);
	if (!nbr && opt->is_set_precision && !opt->precision)
	{
		if (*ptr == 'p')
		{
			write(1, "0x", 2);
			ret += 2;
		}
		ret += fillnchar(ret, opt->width, ' ');
		*res += ret;
		return (ret);
	}
	len = ft_unbr_length(&nbr, 16);
	if (opt->width > len && !opt->left_align)
	{
		if (opt->fill_by_zero && !opt->precision)
		{
			if (opt->show_prefix)
			{
				*ptr == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
				ret += 2;
				ret += fillnchar(len + ret, opt->width, '0');
				opt->show_prefix = 0;
			}
			else
				ret += fillnchar(len, opt->width, '0');
		}
		else if (!(opt->precision > len))
			ret += fillnchar(len + opt->show_prefix * 2,
					opt->width, ' ');
		else if (opt->precision > len)
			ret += fillnchar(opt->precision + opt->show_prefix * 2,
					opt->width, ' ');
		if (opt->show_prefix)
		{
			*ptr == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
			ret += 2;
		}
		if (opt->precision > len)
			ret += fillnchar(len, opt->precision, '0');
		print_hex(nbr, *ptr == 'X' ? 'A' : 'a');
		ret += len;
	}
	else if (opt->width > len && opt->left_align)
	{
		if (opt->show_prefix)
		{
			*ptr == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
			ret += 2;
		}
		if (opt->precision > len)
			ret += fillnchar(len, opt->precision, '0');
		print_hex(nbr, *ptr == 'X' ? 'A' : 'a');
		ret += len;
		ret += fillnchar(ret, opt->width, ' ');
	}
	else
	{
		if (opt->show_prefix)
		{
			*ptr == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
			ret += 2;
		}
		if (opt->precision > len)
			ret += fillnchar(len, opt->precision, '0');
		print_hex(nbr, *ptr == 'X' ? 'A' : 'a');
		ret += len;
	}
	*res += ret;
	return (ret);
}

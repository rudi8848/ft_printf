#include "includes/ft_printf.h"

uintmax_t	ft_cut_unsigned(va_list *args, t_options *options)
{
	uintmax_t nbr;

	nbr = va_arg(*args, uintmax_t);
	if (options->len_l || options->len_ll)
	{
		options->len_h = 0;
		options->len_hh = 0;
	}
	if (options->len_hh)
		nbr = (unsigned char)nbr;
	else if (options->len_h)
		nbr = (unsigned short)nbr;
	else if (options->len_l)
		nbr = (unsigned long)nbr;
	else if (options->len_ll)
		nbr = (unsigned long long)nbr;
	else if (options->len_j)
		nbr = (uintmax_t)nbr;
	else if (options->len_z)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned)nbr;
	return(nbr);
}

intmax_t	ft_cut_signed(va_list *args, t_options *options)
{
	intmax_t nbr;

	nbr = va_arg(*args, intmax_t);
	if (options->len_l || options->len_ll)
	{
		options->len_h = 0;
		options->len_hh = 0;
	}
	if (options->len_hh && !options->len_l)
		nbr = (char)nbr;
	else if (options->len_h && !options->len_l)
		nbr = (short)nbr;
	else if (options->len_l)
		nbr = (long)nbr;
	else if (options->len_ll)
		nbr = (long long)nbr;
	else if (options->len_j)
		nbr = (intmax_t)nbr;
	else if (options->len_z)
		nbr = (ssize_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

int		ft_unbr_length(uintmax_t *n,int  base)
{
	int len;
	uintmax_t nbr;

	len = 0;
	nbr = 0;
	if (*n == 0)
		len++;
	else
	{
		nbr = *n;
		while (nbr)
		{
			nbr /= base;
			len++;
		}
	}
	return (len);
}
int		ft_snbr_length(intmax_t *n,int  base)
{
	int len;
	intmax_t nbr;

	len = 0;
	nbr = 0;
	if (*n == 0)
		len++;
	else if (*n < 0)
	{
		if (base == 10)
			len++;
		nbr = - *n;
	}
	else
		nbr = *n;
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}
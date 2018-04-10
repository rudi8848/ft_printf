#include "includes/ft_printf.h"

int		ft_nb_bits(wint_t wc)
{
 int i = 0;
  while (wc)
  {
    wc/=2;
    i++;
    }
    return i;
}

int ft_nb_bytes(int n)
{
	if (n <= 7)
		return (1);
	else if (n <= 11)
		return (2);
	else if (n <= 16)
		return (3);
	else
		return (4);
}

int   ft_putwchar(wint_t wc)
{
    char    tmp[4];
    int bits;
    int bytes;

    bits = ft_nb_bits(wc);
    bytes = ft_nb_bytes(bits);

    if (bytes <= bits && bytes <= MB_CUR_MAX)
    {
        if (bytes == 1)
            tmp[0] = wc;
        else
        {
            if (bytes == 2)
                tmp[0] = ((wc & (0x1f << 6)) >> 6) | 0xC0;
            else
            {
                if (bytes == 3)
                    tmp[0] = ((wc >> 12) & 0xf) | 0xE0;
                else
                {
                    tmp[0] = ((wc >> 18) & 7) | 0xF0;
                    tmp[1] = ((wc >> 12) & 0x3f) | 0x80;
                }
                tmp[bytes - 2] = ((wc >> 6) & 0x3f) | 0x80;
            }
            tmp[bytes - 1] = (wc & 0x3f) | 0x80;
        }
        write(1, tmp, bytes); 
    }
    return (bytes);
}
#ifndef __FT_PRINTF_H__
# define __FT__PRINF_H_

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>

#define ERROR -1

typedef union u_number
{
	int i;							//<no>
	unsigned u;						//<no>
	size_t st;						//z
	long int l; 						//ld = D
	unsigned long int ul;			//l  O = lo, U = lu
	long long int ll;				//ll
	unsigned long long int ull;	//ll
	short sh;			//h
	unsigned short ush;	//h
	intmax_t ix; 			//j
	uintmax_t uix;			//j
	char ch;				//hh
	unsigned char uch;		//hh
} t_number;


/*
			Modifier      |    d, i      |     o, u, x, X       |     n
         ---------------------------------------------------------------------
         hh                signed char    unsigned char         signed char *
         h                 short          unsigned short        short *
         l (ell)           long           unsigned long         long *
         ll (ell ell)      long long      unsigned long long    long long *
         j                 intmax_t       uintmax_t             intmax_t *		<stdint.h>
         z                 (see note)     size_t                (see note)		<stddef.h> 


*/

typedef		struct s_options
{
	/***----flags----*/
	int				left_align;			//-
	int				show_sign;			//+
	int				space_before;		//' '
	int				show_prefix;		//#
	int				fill_by_zero;		//0

	/***----width-----*/
	int			width;

	/***----precision-----*/
	int			precision;			//.
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

/*
**-----------------------------------BIT MASKS FOR UNICODE-------------------------------------------------
*/

typedef		enum
{
	ONE_B,
	TWO_B,
	THREE_B,
	FOUR_B,
	BIT_MASKS
}e_bit_masks;

size_t	unicode_masks[BIT_MASKS] = {
	0,									//"0xxx xxxx",
	0xC080,			//49280,			//"110x xxxx    10xx xxxx",
	0xE08080,		//14712960,			//"1110 xxxx    10xx xxxx    10xx xxxx",
	0xF0808080		//4034953344		//"1111 0xxx    10xx xxxx    10xx xxxx    10xx xxxx"
};




int		ft_printf(const char *format, ...);


#endif

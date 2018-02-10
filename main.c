#include "ft_printf.h"
/*
**------------------------------------------MAIN------------------------------------------------------------
*/

int main(void)
{
	//printf("--------------------------------------->%s\n", __FUNCTION__);
	
	setlocale(LC_ALL, "Rus");
	
	ft_printf("no args\n");
	//ft_printf("args %0. qwe 15\n");
	ft_printf("arg %%\n");
	ft_printf("%s\n", "hello");
	ft_printf("[%c][%c]\n", 'Q', '7');
	ft_printf("%c %s\n",'0', "qwerty");
//	ft_printf("% %s\n",'0', "qwerty");
  ft_printf("--------------------------------------------------\n");

	ft_printf("my: oct 	%#o\n", 100);
	printf("original: oct 	%#o\n", 100);
  ft_printf("--------------------------------------------------\n");

	ft_printf("string: %s\n", "adsf");
	//ft_printf("pointer: %p", &x);
  ft_printf("--------------------------------------------------\n");
	ft_printf("my hex: 	%X\n", 1234);
	printf("original hex: 	%X\n", 1234 );


	int x = 125;

	//char	*str = "qwerty";
	//wchar_t	*wstr = "фыва";
	char d = 'b';
	wchar_t a = L'Ы';
	wchar_t b = L'ࢢ';
	//wchar_t c = L'𐄂';
//printf("%lu\n", sizeof(wchar_t));
	printf("cur max: %d\n", MB_CUR_MAX);

	wchar_t *wstr = L"привет, друг!!!";


	int arab = L'ڲ';
	wchar_t *rus = L"дарова!!!";
	char *ptr;
	ptr = "Hello world!";
	int i = 5;
	int *np = &i;
	unsigned int size_in_bits = sizeof(int)*8;
	int max_int;
	char buf[80];

	max_int = ~(1 << (size_in_bits-1));
	int min_int = 1 << (size_in_bits - 1);
  ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		%s\n", ptr);
	printf("original: 	%s\n", ptr);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		ft_printf test\n");
	printf("original: 	ft_printf test\n");
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		%S\n", rus);
	printf("original: 	%ls\n", rus);
	ft_printf("--------------------------------------------------\n");
	
	
	ft_printf("my: 		%p pointer\n", np);
	printf("original: 	%p pointer\n", np);
	ft_printf("--------------------------------------------------\n");
	
	ft_printf("my: 		%d = 5\n", i);
	printf("original: 	%d = 5\n", i);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: 		%d =  max int\n", max_int);
	printf("original: 	%d =  max int\n", max_int);
	ft_printf("--------------------------------------------------\n");
	ft_printf("my: 		%d =  min int\n", min_int);
	printf("original: 	%d =  min int\n", min_int);
	ft_printf("--------------------------------------------------\n");


	ft_printf("my: char 	%c = 'a'\n", 'a');
	printf("original: char 	%c = 'a'\n", 'a');
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: hex 	%x = ff\n", 0xff);
	printf("original: hex 	%x = ff\n", 0xff);
	ft_printf("--------------------------------------------------\n");

	ft_printf("my: hex 	%02x = 00\n", 0);
	printf("original: hex 	%02x = 00\n", 0);
	ft_printf("--------------------------------------------------\n");

	/*
	ft_printf("my: signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf("original: signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	ft_printf("--------------------------------------------------\n");
*/
	/*
  
	ft_printf("my: %d %s(s)%", 0, "message");
	printf("original: %d %s(s)%", 0, "message");
	ft_printf("--------------------------------------------------\n");
*/
	ft_printf("my: \n");
	printf("original: \n");
	ft_printf("--------------------------------------------------\n");
	
	ft_printf("my: %o %s(s) with %%\n", 10, "message");
	printf("original: %o %s(s) with %%\n", 10, "message");

	ft_printf("--------------------------------------------------\n");
	printf("	MB_CUR_MAX: %d\n", MB_CUR_MAX);


	ft_printf("--------------------------------------------------\n");

	
	ft_printf("my: %c\n",  arab);
	printf("original:  %c\n",  arab);

	ft_printf("--------------------------------------------------\n");

	//printf("%d\n", size_bin(arab));
	ft_printf("my: %C\n", arab);
	printf("original: %lc\n", arab);


	ft_printf("--------------------------------------------------\n");
	ft_printf("wstr:	%S\n",wstr);	
	printf("wstr:	%ls\n",wstr);

	ft_printf("--------------------------------------------------\n");
	ft_printf("my: 		%d %i %d %i\n", 777, -777, -56879, 0);
	printf("original: 	%d %i %d %i\n", 777, -777, -56879, 0);
	return 0;
}


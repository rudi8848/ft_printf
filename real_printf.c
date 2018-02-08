#include <stdio.h>
//#include <wchar.h>
#include <stdlib.h>
#include <stdint.h>

/*
		ФОРМАТ:
		%[флаги][ширина][.точность][размер]тип


		Флаги[править | править код]
Знак	Название знака	Значение													В отсутствие этого знака						Примечание
-		минус			выводимое значение выравнивается по левому
						краю в пределах минимальной ширины поля						по правому	


+		плюс			всегда указывать знак (плюс или минус) для 
						выводимого десятичного числового значения					только для отрицательных чисел	


 		пробел			помещать перед результатом пробел, если первый
 						символ значения не знак										Вывод может начинаться с цифры.					Символ + имеет больший приоритет, чем пробел. Используется только для десятичных числовых значений.


#		октоторп		«альтернативная форма» вывода значения																		При выводе чисел в формате перед числом будет указываться особенность формата. (см. ниже)


0		ноль			дополнять поле до ширины, указанной в поле
						ширина управляющей последовательности, символом 0			дополнять пробелами								Используется для типов d, i, o, u, x, X, a, A, e, E, f, F, g, G. Для типов d, i, o, u, x, X, если точность указана, этот флаг игнорируется. Для остальных типов поведение не определено.



					__printf (const char *format, ...)
					{
					   va_list arg;
					   int done;
					 
					   va_start (arg, format);
					   done = vfprintf (stdout, format, arg);
					   va_end (arg);
					 
					   return done;
					}

*/


int		main(void)
{
	char *str = "hello, bro!";
	char *str1 = "дратуйти!";
	char *str2 = "こんにちは";

	int		number = ~(1<<31);//2579;
	int		negnumber = 1<<31;
	float 	f = 1.23;
	float 	nf = -1.23;
/*	int		ret;

	printf("%d\n", MB_CUR_MAX);
	ret = printf("s: %25s\n", str);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("s: %s\n", str1);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("s: %s\n", str2);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	real_printf.c:43:26: warning: format specifies type 'wchar_t *' (aka 'int *') but the argument has type
      'char *' [-Wformat]
        ret = printf("S: %S\n", str);
                         ~~     ^~~

	ret = printf("S: %S\n", str);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("p: %p\n", &str);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("d: %-25d\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("D: %D\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("i: %i\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("o: %o\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("O: %O\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("u: %u\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("U: %U\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("x: %x\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("X: %X\n", number);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("c: %c\n", *str);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

	ret = printf("C: %C\n", *str);
	printf("ret is: %d\n", ret);
	printf("------------------------------------------------\n");

*/

	//------------------------------------------
	printf("флаги,ширина и точность\n");
	//------------------------------------------

	printf("width -30: |%-30s|\n", str1);
	printf("width 30: |%30s|\n", str1);
	printf("precision 4: |%.4s|\n", str1);
	printf("precision 4, width: |%30.4s|\n", str1);
	printf("no: |%s|\n", str1);
	printf("\n");

	printf("no:   |%d|\n", number);
	printf("no:   |%d|\n", negnumber);
	printf("no:   |%f|\n", f);
	printf("no:   |%f|\n", nf);
		printf("\n");

	printf("width:   |%30d|\n", number);
	printf("width:   |%30d|\n", negnumber);
	printf("width:   |%30f|\n", f);
	printf("width:   |%30f|\n", nf);
		printf("\n");

	printf("+:   |%+d|\n", number);
	printf("+:   |%+d|\n", negnumber);
	printf("+:   |%+f|\n", f);
	printf("+:   |%+f|\n", nf);
		printf("\n");

	printf("+, width:   |%+30d|\n", number);
	printf("+, width:   |%+30d|\n", negnumber);
	printf("+, width:   |%+30f|\n", f);
	printf("+, width:   |%+30f|\n", nf);
		printf("\n");

	printf("+, -, width:   |%+-30d|\n", number);
	printf("+, -, width:   |%+-30d|\n", negnumber);
	printf("+, -, width:   |%+-30f|\n", f);
	printf("+, -, width:   |%+-30f|\n", nf);
		printf("\n");

	printf("space:   |% d|\n", number);
	printf("space:   |% d|\n", negnumber);
	printf("space:   |% f|\n", f);
	printf("space:   |% f|\n", nf);
		printf("\n");

	

	printf("0:   |%0d|\n", number);
	printf("0:   |%0d|\n", negnumber);
	printf("0:   |%0f|\n", f);
	printf("0:   |%0f|\n", nf);
		printf("\n");

	printf("0, width:   |%030d|\n", number);
	printf("0, width:   |%030d|\n", negnumber);
	printf("0, width:   |%030f|\n", f);
	printf("0, width:   |%030f|\n", nf);
		printf("\n");

	printf("0, space, width:   |%0 30d|\n", number);
	printf("0, space, width:   |%0 30d|\n", negnumber);
	printf("0, space, width:   |%0 30f|\n", f);
	printf("0, space, width:   |%0 30f|\n", nf);
		printf("\n");

	printf("0, +, width:   |%0+30d|\n", number);
	printf("0, +, width:   |%0+30d|\n", negnumber);
	printf("0, +, width:   |%0+30f|\n", f);
	printf("0, +, width:   |%0+30f|\n", nf);
		printf("\n");

	printf("x:   |%x|\n", number);
	printf("x:   |%x|\n", negnumber);
	printf("a, width:   |%a|\n", f);
	printf("a, width:   |%a|\n", nf);
		printf("\n");

	printf("#x:   |%#x|\n", number);
	printf("#x:   |%#x|\n", negnumber);
	printf("#a, width:   |%#a|\n", f);
	printf("#a, width:   |%#a|\n", nf);
		printf("\n");

	printf("#o:   |%#o|\n", number);
	printf("#o:   |%#o|\n", negnumber);
	printf("A, width:   |%A|\n", f);
	printf("A, width:   |%A|\n", nf);
		printf("\n");

	printf("+x:   |%+x|\n", number);
	printf("+x:   |%+x|\n", negnumber);
	printf("+o:   |%+o|\n", number);
	printf("+o:   |%+o|\n", negnumber);
		printf("\n");

printf("no precision:   |%f|\n", f);
	printf("no precision:   |%f|\n", nf);
	printf("precision.2:   |%.2f|\n", f);
	printf("precision.2:   |%.2f|\n", nf);
	printf("precision.2:   |%.2d|\n", number);
	printf("precision.2:   |%.2d|\n", negnumber);
	printf("precision.:   |%.f|\n", f);
	printf("precision.:   |%.f|\n", nf);
	printf("precision.:   |%.d|\n", number);
	printf("precision.:   |%.d|\n", negnumber);
	printf("precision.-2:   |%.*f|\n",-2,f);
	printf("precision.-2:   |%.*f|\n",-2, nf);
	printf("precision.-2:   |%.*d|\n",-2, number);
	printf("precision.-2:   |%.*d|\n",-2, negnumber);
		printf("\n");
	printf("------------------------------LENGTH MODIFIERS------------------------\n");

	printf("hh:		%hhd\n", number);
	printf("hh:		%hhd\n", negnumber);
	printf("h:		%hd\n", number);
	printf("h:		%hd\n", negnumber);
	printf("l:		%ld\n", number);
	printf("l:		%ld\n", negnumber);
	printf("ll:		%lld\n", number);
	printf("ll:		%lld\n", negnumber);
	printf("j:		%jd\n", number);
	printf("j:		%jd\n", negnumber);
	printf("z:		%zd\n", number);
	printf("z:		%zd\n", negnumber);

	printf("------------------------------LENGTH SIZES------------------------\n");
	printf("char:				%zu\n", sizeof(char));
	printf("unsigned char:		%zu\n", sizeof(unsigned char));
	printf("short:				%zu\n", sizeof(short));
	printf("unsigned short:		%zu\n", sizeof(unsigned short));
	printf("long:				%zu\n", sizeof(long));
	printf("unsigned long:		%zu\n", sizeof(unsigned long));
	printf("long long:			%zu\n", sizeof(long long));
	printf("unsigned long long:	%zu\n", sizeof(unsigned long long));
	printf("intmax_t:			%zu\n", sizeof(intmax_t));
	printf("uintmax_t:			%zu\n", sizeof(uintmax_t));
	printf("size_t:				%zu\n", sizeof(size_t));
	printf("ssize_t:			%zu\n", sizeof(ssize_t));
	return 0;
}
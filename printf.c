#include "printf.h"

int ft_printf(const char *format, ...)
{
	va_list args;
	int count;

	va_start (args, format);
	count = 0;
	while(*format != '\0')
	{

		if(*format == '%')
		{
			format ++;
			if(*format == '\0')
				break;
			count = count + check_specifier(*format, &args);
			format ++;
		}
		else
		{	
			write(1,&*format,1);
			format ++;
			count ++;
		}
	}
	va_end(args);
	return (count);
}

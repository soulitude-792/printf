#include "printf.h"

int ft_printf(const char *format, ...)
{
	va_list args;
	int count;
	int written;

	va_start (args, format);
	count = 0;
	while(*format != '\0')
	{

		if(*format == '%')
		{
			format ++;
			if(*format == '\0')
			{
				va_end(args);
				return (-1);
			}
			written = check_specifier(*format, &args);
			if(written == -1)
			{
				va_end(args);
				return (-1);
			}
			count = count + written;
			format ++;
		}
		else
		{	
			written = write(1,format,1);
			if(written == -1)
			{
				va_end(args);
				return (-1);
			}
			format ++;
			count += written;
		}
	}
	va_end(args);
	return (count);
}

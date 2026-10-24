#include "printf.h"

static int check_num(char c, va_list *args)
{
	int			 num;
	unsigned int	unum;

	if(c == 'd' || c == 'i')
	{
		num = va_arg(*args, int);
		return (ft_putnbr(num));
	}
	else if(c == 'u')
	{
		unum = va_arg(*args, unsigned int);
		return (ft_putunbr(unum));
	}
	else if(c == 'x')
		return (puthex(va_arg(*args, unsigned int), "0123456789abcdef"));
	else if(c == 'X')
		return (puthex(va_arg(*args, unsigned int), "0123456789ABCDEF"));
	else if(c == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else
		return (0);
}

int check_specifier(char c, va_list *args)
{
	char	ch;
	char	*str;

	if(c == 'c')
	{
		ch = va_arg(*args, int);
		return (ft_putchar(ch));
	}
	else if(c == 's')
	{
		str = va_arg(*args, char *);
		return (ft_putstr(str));
	}
	else if(c == '%')
		return (ft_putchar('%'));
	else
		return (check_num(c, args));
}

int ft_putptr(void *ptr)
{
	unsigned long long	pnum;
	int	temp;

	pnum = (unsigned long long)ptr;
	if(pnum == 0)
		return (write(1, "(nil)", 5));
	if (write(1, "0x", 2) == -1)
		return (-1);
	temp = puthex(pnum, "0123456789abcdef");
	if(temp == -1)
		return (-1);
	return (2 + temp);
}

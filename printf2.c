#include "printf.h"

int ft_putchar(char c)
{
        return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
        int     i;

        if(s == NULL)
                return (write(1, "(null)", 6));
        i = 0;
        while(s[i])
        {
                write(1, &s[i], 1);
                i++;
        }
        return (i);
}

int ft_putunbr(unsigned int un)
{
        int     count;

        count = 0;
        if(un >= 10)
        {
                count = count + ft_putunbr(un / 10);
        }
        ft_putchar((un % 10) + '0');
        return (count + 1);
}

int ft_putnbr(int n)
{
        long    ln;
        int     count;

        count = 0;
        ln = n;
        if (ln < 0)
        {
                ft_putchar('-');
                ln = -ln;
                count ++;
        }
        if (ln >= 10)
        {
                count = count + ft_putnbr(ln / 10);
        }
        ft_putchar((ln % 10) + '0');
        return(count + 1);
}

int puthex(unsigned long long n, char *base)
{
        int     count;

        count = 0;
        if(n >= 16)
                count = puthex(n / 16, base);
        ft_putchar(base[n % 16]);
        return (count + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imigdady <imigdady@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 08:47:26 by imigdady          #+#    #+#             */
/*   Updated: 2026/10/27 08:47:29 by imigdady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	if (s == NULL)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putunbr(unsigned int un)
{
	int	count;

	count = 0;
	if (un >= 10)
	{
		count = count + ft_putunbr(un / 10);
	}
	if (ft_putchar((un % 10) + '0') == -1)
		return (-1);
	return (count + 1);
}

int	ft_putnbr(int n)
{
	long	ln;
	int		count;
	int		temp;

	count = 0;
	ln = n;
	if (ln < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		ln = -ln;
		count++;
	}
	if (ln >= 10)
	{
		temp = ft_putnbr(ln / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	if (ft_putchar((ln % 10) + '0') == -1)
		return (-1);
	return (count + 1);
}

int	puthex(unsigned long long n, char *base)
{
	int	count;
	int	temp;

	count = 0;
	if (n >= 16)
	{
		temp = puthex(n / 16, base);
		if (temp == -1)
			return (-1);
		count = temp;
	}
	if (ft_putchar(base[n % 16]) == -1)
		return (-1);
	return (count + 1);
}

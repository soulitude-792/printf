/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imigdady <imigdady@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 08:47:11 by imigdady          #+#    #+#             */
/*   Updated: 2026/10/27 08:47:16 by imigdady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_format(const char **format, va_list *args)
{
	int	written;

	(*format)++;
	if (**format == '\0')
		return (-1);
	written = check_specifier(**format, args);
	if (written == -1)
		return (-1);
	(*format)++;
	return (written);
}

static int	ft_handle_char(const char **format)
{
	int	written;

	written = write(1, *format, 1);
	if (written == -1)
		return (-1);
	(*format)++;
	return (written);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		written;

	va_start(args, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			written = ft_handle_format(&format, &args);
		else
			written = ft_handle_char(&format);
		if (written == -1)
		{
			va_end(args);
			return (-1);
		}
		count = count + written;
	}
	va_end(args);
	return (count);
}

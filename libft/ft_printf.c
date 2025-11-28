/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:28:04 by elleagn           #+#    #+#             */
/*   Updated: 2024/09/18 16:28:05 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printvar(char c, va_list *args)
{
	if (c == '%')
		return (ft_printchar('%'));
	if (c == 'c')
		return (ft_printchar(va_arg(*args, int)));
	if (c == 's')
		return (ft_printstring(va_arg(*args, char *)));
	if (c == 'p')
		return (ft_printptr(va_arg(*args, int *)));
	if (c == 'i' || c == 'd')
		return (ft_printnbr(va_arg(*args, int), 10, "0123456789"));
	if (c == 'u')
		return (ft_printul(va_arg(*args, unsigned), 10, "0123456789"));
	if (c == 'x')
		return (ft_printul((unsigned)va_arg(*args, int), \
			16, "0123456789abcdef"));
	if (c == 'X')
		return (ft_printul((unsigned)va_arg(*args, int), \
			16, "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg_ptr;
	int		i;
	int		printnbr;

	if (s == 0)
		return (-1);
	i = 0;
	printnbr = 0;
	va_start(arg_ptr, s);
	while (s[i])
	{
		if (s[i] != '%')
			printnbr += ft_printchar(s[i]);
		else
		{
			printnbr += ft_printvar(s[i + 1], &arg_ptr);
			i++;
		}
		i++;
	}
	va_end(arg_ptr);
	return (printnbr);
}

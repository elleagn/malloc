/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 06:37:04 by gozon             #+#    #+#             */
/*   Updated: 2024/06/03 06:41:09 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int nbr, int size, char *base)
{
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		return (ft_printul((unsigned)(-1 * nbr), size, base) + 1);
	}
	else
		return (ft_printul((unsigned)nbr, size, base));
}

int	ft_printul(unsigned long int n, int size, char *base)
{
	int	count;

	if (n < (unsigned long) size)
	{
		ft_putchar_fd(base[n], 1);
		return (1);
	}
	else
	{
		count = (1 + ft_printul(n / (unsigned)size, size, base));
		ft_putchar_fd(base[n % (unsigned)size], 1);
		return (count);
	}
}

int	ft_printptr(void *ptr)
{
	if (!ptr)
		return (ft_printstring("(nil)"));
	ft_putstr_fd("0x", 1);
	return (ft_printul((unsigned long)ptr, 16, "0123456789abcdef") + 2);
}

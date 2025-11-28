/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 06:37:55 by gozon             #+#    #+#             */
/*   Updated: 2024/06/03 06:45:00 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printstring(char *s)
{
	int	i;

	if (!s)
		return (ft_printstring("(null)"));
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
	return (ft_strlen(s));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:22:47 by elleagn           #+#    #+#             */
/*   Updated: 2024/07/08 09:05:34 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_printchar(int c);
int	ft_printstring(char *s);
int	ft_printnbr(int n, int size, char *base);
int	ft_printptr(void *ptr);
int	ft_printul(unsigned long int n, int size, char *base);

#endif

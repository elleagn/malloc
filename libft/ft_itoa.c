/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:18:16 by gozon             #+#    #+#             */
/*   Updated: 2024/05/24 14:31:57 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_powten(long int nbr)
{
	int	pow;

	pow = 1;
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr / pow > 9)
		pow = pow * 10;
	return (pow);
}

int	ft_digitnbr(long int nbr)
{
	int	digits;
	int	pow;

	digits = 2;
	pow = 1;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		digits = digits + 1;
	}
	while (nbr / pow > 9)
	{
		pow = pow * 10;
		digits = digits + 1;
	}
	return (digits);
}

char	*ft_initres(size_t *i, long int *nbr)
{
	char	*res;
	int		digits;

	digits = ft_digitnbr(*nbr);
	res = malloc((digits) * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (*nbr < 0)
	{
		res[0] = '-';
		*nbr = *nbr * -1;
		*i = *i + 1;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			powten;
	long int	nbr;
	size_t		i;

	nbr = n;
	powten = ft_powten(nbr);
	i = 0;
	res = ft_initres(&i, &nbr);
	if (res == NULL)
		return (NULL);
	while (powten)
	{
		res[i] = (nbr / powten) + '0';
		nbr = nbr % powten;
		powten = powten / 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:00:52 by gozon             #+#    #+#             */
/*   Updated: 2024/05/27 10:13:04 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (lst == NULL)
		return (0);
	count = 1;
	while (lst->next)
	{
		lst = lst->next;
		count = count + 1;
	}
	return (count);
}

/*
int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("bwlbcdb");
	new = ft_lstnew("hbdccb");
	ft_lstadd_front(&lst, new);
	new = ft_lstnew("wvkcvk");
	ft_lstadd_front(&lst, new);
	ft_putnbr_fd(ft_lstsize(lst), 1);
	return (0);
}
*/
